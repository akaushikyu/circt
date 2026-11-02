"""Query API, local server and agent bridge for loopschedule-vis.

Three front ends share one table of query commands (COMMANDS):

  * `loopschedule-vis query ...` answers a single query on the command line,
    either offline from an IR/JSON file or against a running server.
  * `loopschedule-vis serve ...` serves the interactive page over HTTP together
    with a JSON API (GET /api/<command>), records what the user is looking at
    in the browser (POST /api/selection) and forwards questions typed into the
    page to a coding agent (POST /api/ask; `claude -p` by default).
  * The agent itself calls the same API back with curl while it answers.

AGENTS.md in this directory documents the API for agents. Only the Python 3
standard library is used.
"""

import collections
import json
import os
import re
import shlex
import shutil
import subprocess
import sys
import threading
import time
import urllib.error
import urllib.parse
import urllib.request
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
REPO_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
AGENTS_DOC = os.path.join(SCRIPT_DIR, 'AGENTS.md')
SERVER_ENV = 'LOOPSCHEDULE_VIS_SERVER'
DEFAULT_PORT = 8765

SSA_RE = re.compile(r'%[A-Za-z0-9_.$-]+(?:#\d+)?')
MAX_ITEMS = 200  # cap on list lengths in query results
MAX_CONTEXT = 14000  # cap on each context block handed to the agent


class QueryError(Exception):
  pass


def _short(text, limit):
  return text if len(text) <= limit else text[:limit] + ' …'


def _capped(items, limit=MAX_ITEMS):
  items = list(items)
  if len(items) <= limit:
    return items, None
  return items[:limit], '%d more not shown' % (len(items) - limit)


def _to_int(name, value):
  try:
    return int(value)
  except (TypeError, ValueError):
    raise QueryError('%s must be an integer, got %r' % (name, value))


def _flag(value):
  return str(value).lower() not in ('', '0', 'false', 'no', 'off')


# ----------------------------------------------------------------------------
# Command table
# ----------------------------------------------------------------------------

# name -> (positional params, optional params, one-line description).
# On HTTP, every param may also be passed as a query parameter
# (/api/stage?pipeline=0&stage=3), and positionals as path segments
# (/api/stage/0/3).
COMMANDS = collections.OrderedDict([
    ('help', ([], [], 'This command list.')),
    ('summary', ([], [], 'Kernel overview: source, functions and a brief of '
                 'every pipeline (II, trip count, depth, latency, port '
                 'demand).')),
    ('function', (['ref'], [], 'One function by id or name: its source span '
                  'text and pipeline briefs.')),
    ('pipeline', (['pipeline'], [], 'One pipeline: nest, iter_args, per-stage '
                  'summary, loop-carried edges with slack, modulo reservation '
                  'table.')),
    ('stage', (['pipeline', 'stage'], ['consts'], 'One stage: its ops with '
               'inputs/outputs, memory accesses per memref, MRT column.')),
    ('op',
     (['id'], [], 'One op by id: full text, cycles, every input and '
      'output edge, operands defined outside the pipeline, source line.')),
    ('value', (['name'], ['pipeline', 'stage'], 'A variable: an SSA name '
               '(%12, %s#3, %arg4) or a C/source name (A, tmp). Definitions, '
               'uses, edges, iter_args, memrefs, matching source lines.')),
    ('memref', (['name'], ['pipeline'], 'A memref by label or SSA name: every '
                'access by pipeline/stage and its MRT rows.')),
    ('line', (['line'], [], 'A source line: its text, function and the ops '
              'mapped to it.')),
    ('search', (['q'], ['pipeline', 'limit'], 'Ops whose name or text '
                'contains q (case-insensitive).')),
    ('cdfg', (['pipeline'], ['stage', 'consts'], 'The pipeline (or one '
              'stage) as compact text: every op with its incoming edges. '
              'Returns {"text": ...}; the CLI prints the text.')),
    ('ir', (['from'], ['to'], 'Lines of the loopschedule IR (1-based, '
            'inclusive; at most 400).')),
    ('src', (['from'], ['to'], 'Lines of the source file shown in the left '
             'pane (1-based, inclusive; at most 400).')),
    ('selection', ([], [], 'Server only: what the user is looking at in the '
                   'browser right now, plus the resolved context (stage, '
                   'focused op, selected variable, source line).')),
    ('ping', ([], [], 'Server only: liveness and whether an agent is '
              'configured.')),
])
SERVER_ONLY = ('selection', 'ping')


def help_text():
  out = []
  for name, (pos, opt, doc) in COMMANDS.items():
    sig = ' '.join(['<%s>' % p for p in pos] + ['[--%s X]' % o for o in opt])
    out.append({'command': name, 'args': sig, 'doc': doc})
  return {
      'commands': out,
      'http': 'GET /api/<command>?<param>=<value>&... (positionals may also '
              'be path segments: /api/stage/0/3). URL-encode %% as %%25.',
      'docs': AGENTS_DOC,
  }


# ----------------------------------------------------------------------------
# Query index over the extracted schedule data
# ----------------------------------------------------------------------------


class QueryIndex:
  """Answers COMMANDS over the dict produced by loopschedule_vis.build_data.

  If the data carries 'io' (full result and operand lists per op, present in
  freshly built data and in --json output) it is used for variable lookups;
  otherwise operands are recovered from the op text.
  """

  def __init__(self, data, ir_text=None):
    self.data = data
    self.ops = data['ops']
    self.pipes = data['pipelines']
    self.fns = data['functions']
    self.mem = data['memrefs']
    self.io = data.get('io') or []
    self.src_lines = data['source']['lines']
    self.ir_lines = ir_text.splitlines() if ir_text is not None else None
    if self.ir_lines is None and data['source']['mode'] == 'ir':
      self.ir_lines = self.src_lines
    self.in_edges = collections.defaultdict(list)
    self.out_edges = collections.defaultdict(list)
    for p in self.pipes:
      for e in p['edges']:
        self.in_edges[e['t']].append(e)
        self.out_edges[e['f']].append(e)
    self.line_ops = collections.defaultdict(list)
    self.mem_ops = collections.defaultdict(list)
    for o in self.ops:
      if o['src'] is not None:
        self.line_ops[o['src']].append(o['id'])
      if o['m']:
        self.mem_ops[o['m']].append(o['id'])

  # ---- dispatch ----

  def dispatch(self, cmd, params=None, positional=()):
    if cmd not in COMMANDS:
      raise QueryError('unknown command %r; try "help"' % cmd)
    if cmd in SERVER_ONLY:
      raise QueryError('"%s" needs a running server (loopschedule-vis serve)' %
                       cmd)
    pos, opt, _ = COMMANDS[cmd]
    params = dict(params or {})
    if len(positional) > len(pos):
      raise QueryError('%s takes at most %d positional argument(s)' %
                       (cmd, len(pos)))
    for k, v in zip(pos, positional):
      params[k] = v
    # Forgiving aliases: p/s for pipeline/stage, id for a lone positional.
    for alias, real in (('p', 'pipeline'), ('s', 'stage')):
      if alias in params and real in pos + opt and real not in params:
        params[real] = params.pop(alias)
    if 'id' in params and 'id' not in pos and len(
        pos) == 1 and pos[0] not in params:
      params[pos[0]] = params.pop('id')
    unknown = set(params) - set(pos) - set(opt)
    if unknown:
      raise QueryError('%s: unknown parameter(s) %s' %
                       (cmd, ', '.join(sorted(unknown))))
    missing = [k for k in pos if k not in params]
    if missing:
      raise QueryError('%s: missing %s' % (cmd, ', '.join(missing)))
    return getattr(self, 'q_' + cmd)(**params)

  # ---- helpers ----

  def _op(self, oid):
    oid = _to_int('id', oid)
    if not 0 <= oid < len(self.ops):
      raise QueryError('no op #%d (ops are 0..%d)' % (oid, len(self.ops) - 1))
    return oid

  def _pipe(self, pid):
    pid = _to_int('pipeline', pid)
    if not 0 <= pid < len(self.pipes):
      raise QueryError('no pipeline P%d (pipelines are 0..%d)' %
                       (pid, len(self.pipes) - 1))
    return pid

  def _stage(self, pid, s):
    s = _to_int('stage', s)
    if not 0 <= s < len(self.pipes[pid]['stages']):
      raise QueryError('P%d has no stage S%d (stages are 0..%d)' %
                       (pid, s, len(self.pipes[pid]['stages']) - 1))
    return s

  def results_of(self, oid):
    if oid < len(self.io) and self.io[oid]:
      return self.io[oid]['results']
    return [r.strip() for r in self.ops[oid]['r'].split(',') if '%' in r]

  def operands_of(self, oid):
    if oid < len(self.io) and self.io[oid]:
      return self.io[oid]['operands']
    o = self.ops[oid]
    k = o['t'].find(o['n'])
    return SSA_RE.findall(o['t'][k + len(o['n']):] if k >= 0 else o['t'])

  def mem_label(self, key):
    m = self.mem.get(key)
    return m['label'] if m else key

  def fn_name(self, fid):
    return self.fns[fid]['name'] if fid is not None else None

  def cycles(self, o):
    S = self.pipes[o['p']]['stages'][o['s']]
    return [S['start'], S['end']]

  def ref(self, oid):
    o = self.ops[oid]
    res = ', '.join(self.results_of(oid)[:2])
    return 'op #%d %s%s (P%d·S%d)' % (oid, res + ' = ' if res else '', o['n'],
                                      o['p'], o['s'])

  def brief(self, oid, text_limit=200):
    o = self.ops[oid]
    b = collections.OrderedDict([
        ('id', oid),
        ('op', o['n']),
        ('results', self.results_of(oid)),
        ('pipeline', o['p']),
        ('stage', o['s']),
        ('cycles', self.cycles(o)),
        ('category', o['c']),
        ('src_line', o['src']),
        ('ir_line', o['ir']),
        ('text', _short(o['t'], text_limit)),
    ])
    if o['m']:
      b['memref'] = self.mem_label(o['m'])
    return b

  def edge_in(self, e):
    return collections.OrderedDict([('value', e['v']),
                                    ('from', self.ref(e['f'])),
                                    ('from_id', e['f']), ('kind', e['k']),
                                    ('reg_hops', e['h'])])

  def edge_out(self, e):
    return collections.OrderedDict([('value', e['v']), ('to', self.ref(e['t'])),
                                    ('to_id', e['t']), ('kind', e['k']),
                                    ('reg_hops', e['h'])])

  def edge_in_str(self, e):
    return '%s <- #%d %s%s' % (e['v'], e['f'], e['k'], ' (%d reg hop%s)' %
                               (e['h'], '' if e['h'] == 1 else 's')
                               if e['h'] else '')

  def edge_out_str(self, e):
    return '#%d via %s %s' % (e['t'], e['v'], e['k'])

  def mrt_rows(self, P):
    rows = []
    for row in P['mrt']:
      total = [a + b for a, b in zip(row['loads'], row['stores'])]
      peak = max(total) if total else 0
      rows.append(
          collections.OrderedDict([
              ('memref', self.mem_label(row['m'])),
              ('ssa',
               self.mem[row['m']]['ssa'] if row['m'] in self.mem else None),
              ('loads', row['loads']),
              ('stores', row['stores']),
              ('total', total),
              ('peak', peak),
              ('over_dual_port', peak > 2),
          ]))
    return rows

  def pipe_brief(self, pid):
    P = self.pipes[pid]
    n_ops = n_mem = 0
    for S in P['stages']:
      for i in S['ops']:
        c = self.ops[i]['c']
        n_ops += c != 'const'
        n_mem += c == 'memory'
    mrt = self.mrt_rows(P)
    return collections.OrderedDict([
        ('id', pid),
        ('function', self.fn_name(P['func'])),
        ('II', P['II']),
        ('trip_count', P['trip_count']),
        ('depth', len(P['stages'])),
        ('latency', P['latency']),
        ('ops', n_ops),
        ('mem_ops', n_mem),
        ('edges', dict(collections.Counter(e['k'] for e in P['edges']))),
        ('peak_port_demand', max([r['peak'] for r in mrt] or [0])),
        ('over_dual_port', [r['memref'] for r in mrt if r['over_dual_port']]),
        ('src_line', P['src']),
        ('ir_line', P['ir_line']),
    ])

  def _lines(self, lines, frm, to, what):
    if lines is None:
      raise QueryError('%s text is not available' % what)
    frm = max(1, _to_int('from', frm))
    to = _to_int('to', to) if to is not None else frm + 39
    to = min(len(lines), to, frm + 399)
    return {
        'from': frm,
        'to': to,
        'total': len(lines),
        'lines': ['%d: %s' % (n, lines[n - 1]) for n in range(frm, to + 1)]
    }

  # ---- commands ----

  def q_help(self):
    return help_text()

  def q_summary(self):
    d = self.data
    return collections.OrderedDict([
        ('title', d['title']),
        ('input', d['input']),
        ('ir', d['ir']),
        ('source', {
            'path': d['source']['path'],
            'mode': d['source']['mode'],
            'lang': d['source']['lang'],
            'lines': len(self.src_lines)
        }),
        ('counts', {
            'functions': len(self.fns),
            'pipelines': len(self.pipes),
            'stages': sum(len(p['stages']) for p in self.pipes),
            'ops': len(self.ops)
        }),
        ('warnings', d['warnings'][:20]),
        ('functions', [
            collections.OrderedDict([
                ('id', f['id']), ('name', f['name']), ('span', f['span']),
                ('args', f['args']),
                ('pipelines', [self.pipe_brief(pid) for pid in f['pipelines']])
            ]) for f in self.fns
        ]),
    ])

  def q_function(self, ref):
    f = None
    if str(ref).isdigit() and int(ref) < len(self.fns):
      f = self.fns[int(ref)]
    else:
      for g in self.fns:
        if g['name'] == ref:
          f = g
          break
    if f is None:
      raise QueryError('no function %r (have: %s)' %
                       (ref, ', '.join(g['name'] for g in self.fns)))
    text = None
    if f['span']:
      a, b = f['span']
      text = [
          '%d: %s' % (n, self.src_lines[n - 1])
          for n in range(a,
                         min(b, a + 299) + 1)
      ]
    return collections.OrderedDict([
        ('id', f['id']), ('name', f['name']), ('span', f['span']),
        ('args', f['args']), ('source', text),
        ('pipelines', [self.pipe_brief(pid) for pid in f['pipelines']])
    ])

  def q_pipeline(self, pipeline):
    pid = self._pipe(pipeline)
    P = self.pipes[pid]
    II = P['II']
    stages = []
    for k, S in enumerate(P['stages']):
      ids = S['ops']
      srcs = sorted({self.ops[i]['src'] for i in ids} - {None})
      stages.append(
          collections.OrderedDict([
              ('stage', k), ('start', S['start']), ('end', S['end']),
              ('ops', sum(self.ops[i]['c'] != 'const' for i in ids)),
              ('constants', sum(self.ops[i]['c'] == 'const' for i in ids)),
              ('mem_ops', sum(self.ops[i]['c'] == 'memory' for i in ids)),
              ('regs_out', S['regs']), ('when', S['when']),
              ('src_lines', srcs[:30])
          ]))
    carried = []
    for e in P['edges']:
      if e['k'] != 'carried':
        continue
      ps = P['stages'][self.ops[e['f']]['s']]
      cs = P['stages'][self.ops[e['t']]['s']]
      carried.append(
          collections.OrderedDict([('value', e['v']),
                                   ('from', self.ref(e['f'])),
                                   ('to', self.ref(e['t'])),
                                   ('reg_hops', e['h']),
                                   ('produced_by_cycle', ps['end']),
                                   ('needed_at_cycle', cs['start'] + II),
                                   ('slack', cs['start'] + II - ps['end'])]))
    iters = []
    for it in P['iter_args']:
      iters.append(
          collections.OrderedDict([('name', it['name']), ('init', it['init']),
                                   ('next', it['next']),
                                   ('producer', self.ref(it['producer'])
                                    if it['producer'] is not None else None),
                                   ('reg_hops', it['hops'])]))
    out = self.pipe_brief(pid)
    out.update([
        ('nest', P['nest']),
        ('iter_args', iters),
        ('results', P['results']),
        ('stages', stages),
        ('carried_edges', carried),
        ('carried_note', 'slack = needed_at_cycle (consumer stage start + II, '
         'in the next iteration) - produced_by_cycle (producer stage end). '
         'Stage-granular estimate; negative means the recurrence spans more '
         'than II under this model.'),
        ('mrt', self.mrt_rows(P)),
        ('mrt_note', 'Modulo reservation table: accesses per memref at cycle '
         '(stage start mod II); >2 exceeds a dual-port BRAM.'),
    ])
    return out

  def q_stage(self, pipeline, stage, consts=False):
    pid = self._pipe(pipeline)
    s = self._stage(pid, stage)
    P = self.pipes[pid]
    S = P['stages'][s]
    consts = _flag(consts)
    ops = []
    hidden = 0
    per_mem = collections.OrderedDict()
    for i in S['ops']:
      o = self.ops[i]
      if o['m']:
        c = per_mem.setdefault(self.mem_label(o['m']), {
            'loads': 0,
            'stores': 0
        })
        c['stores' if o['n'].endswith('store') else 'loads'] += 1
      if o['c'] == 'const' and not consts:
        hidden += 1
        continue
      b = self.brief(i, 160)
      b['inputs'] = [self.edge_in_str(e) for e in self.in_edges[i]]
      b['outputs'] = [self.edge_out_str(e) for e in self.out_edges[i]]
      ops.append(b)
    ops, more = _capped(ops)
    col = S['start'] % max(P['II'], 1)
    out = collections.OrderedDict([
        ('pipeline', pid), ('stage', s), ('start', S['start']),
        ('end', S['end']), ('mrt_column', col), ('when', S['when']),
        ('regs_out', S['regs']), ('memory', per_mem), ('ops', ops),
        ('constants_hidden', hidden),
        ('edge_legend', 'inputs "%v <- #N kind (k reg hops)": operand %v is '
         'produced by op #N; outputs "#N via %v kind": op #N consumes it. '
         'comb = same stage, reg = from an earlier stage through stage '
         'registers, carried = from the previous iteration (+II).')
    ])
    if more:
      out['ops_truncated'] = more
    return out

  def q_op(self, id):
    oid = self._op(id)
    o = self.ops[oid]
    P = self.pipes[o['p']]
    out = self.brief(oid, 10**6)
    out['function'] = self.fn_name(P['func'])
    out['II'] = P['II']
    ins = self.in_edges[oid]
    out['inputs'] = [self.edge_in(e) for e in ins]
    out['outputs'] = [self.edge_out(e) for e in self.out_edges[oid]]
    fed = {e['v'] for e in ins}
    out['external_operands'] = [
        t for t in dict.fromkeys(self.operands_of(oid)) if t not in fed
    ]
    out['external_note'] = ('operands with no edge: constants, loop IVs, '
                            'function arguments or memrefs defined outside '
                            'the pipeline')
    if o['src'] is not None and o['src'] <= len(self.src_lines):
      out['src_text'] = self.src_lines[o['src'] - 1].strip()
    if self.ir_lines and o['ir'] <= len(self.ir_lines):
      out['ir_text'] = self.ir_lines[o['ir'] - 1].strip()
    if o['m']:
      rows = [
          r for r in self.mrt_rows(P) if r['memref'] == self.mem_label(o['m'])
      ]
      out['memref_mrt_row'] = rows[0] if rows else None
    return out

  def _ops_in(self, pid, s):
    if pid is None:
      return range(len(self.ops))
    return [
        i for i in range(len(self.ops))
        if self.ops[i]['p'] == pid and (s is None or self.ops[i]['s'] == s)
    ]

  def q_value(self, name, pipeline=None, stage=None):
    name = str(name).strip()
    if not name:
      raise QueryError('value: empty name')
    pid = self._pipe(pipeline) if pipeline is not None else None
    s = self._stage(pid,
                    stage) if stage is not None and pid is not None else None
    out = collections.OrderedDict([('query', name), ('pipeline', pid),
                                   ('stage', s)])

    def matches(tok):
      return tok == name or tok.startswith(name + '#')

    if name.startswith('%'):
      defs, uses = [], []
      for i in self._ops_in(pid, s):
        if any(matches(r) for r in self.results_of(i)):
          b = self.brief(i)
          b['consumers'] = [self.edge_out_str(e) for e in self.out_edges[i]]
          defs.append(b)
        toks = [t for t in dict.fromkeys(self.operands_of(i)) if matches(t)]
        for t in toks:
          srcs = [e for e in self.in_edges[i] if e['v'] == t]
          u = collections.OrderedDict([('use', self.ref(i)), ('id', i),
                                       ('token', t)])
          if srcs:
            u['producers'] = [self.edge_in(e) for e in srcs]
          else:
            u['producers'] = ('defined outside the pipeline (constant, loop '
                              'IV, function argument or memref)')
          uses.append(u)
      out['definitions'], more_d = _capped(defs)
      out['uses'], more_u = _capped(uses)
      if more_d or more_u:
        out['truncated'] = [x for x in (more_d, more_u) if x]
      out['iter_args'] = [
          collections.OrderedDict([
              ('pipeline', p['id']), ('name', it['name']), ('init', it['init']),
              ('next', it['next']),
              ('producer',
               self.ref(it['producer']) if it['producer'] is not None else None)
          ]) for p in self.pipes if pid is None or p['id'] == pid
          for it in p['iter_args'] if name in (it['name'], it['next'])
      ]
      out['function_args'] = [{
          'function': f['name'],
          'ssa': name,
          'c_name': f['args'][name]
      } for f in self.fns if name in f['args']]
      keys = [k for k, m in self.mem.items() if m['ssa'] == name]
      out['note'] = ('SSA names are scoped per region: every stage body '
                     'restarts numbering, so one name can denote unrelated '
                     'values in different stages/pipelines. Narrow with '
                     'pipeline/stage.')
    else:
      keys = [k for k, m in self.mem.items() if m['label'] == name]
      out['function_args'] = [{
          'function': f['name'],
          'ssa': ssa,
          'c_name': c
      } for f in self.fns for ssa, c in f['args'].items() if c == name]
      word = re.compile(r'(?<![\w$.])' + re.escape(name) + r'(?![\w$])')
      hits = []
      for n, text in enumerate(self.src_lines, 1):
        if word.search(text):
          ids = [
              i for i in self.line_ops.get(n, ())
              if pid is None or self.ops[i]['p'] == pid
          ]
          hits.append(
              collections.OrderedDict([('line', n), ('text', text.strip()),
                                       ('ops', [self.ref(i) for i in ids][:40])
                                      ]))
      out['source_lines'], more = _capped(hits, 60)
      if more:
        out['source_lines_truncated'] = more
      out['note'] = ('Source names reach the schedule only as memref labels '
                     '(allocas/params) and via op source locations. Scalars '
                     'promoted to registers show up as the ops on their '
                     'source lines; query their SSA names for dataflow.')
    out['memrefs'] = [self._memref(k, pid) for k in keys]
    return out

  def _memref(self, key, pid=None):
    m = self.mem[key]
    acc = collections.OrderedDict()
    for i in self.mem_ops.get(key, ()):
      o = self.ops[i]
      if pid is not None and o['p'] != pid:
        continue
      P = self.pipes[o['p']]
      start = P['stages'][o['s']]['start']
      acc.setdefault('P%d' % o['p'], []).append(
          collections.OrderedDict([
              ('stage', o['s']),
              ('kind', 'store' if o['n'].endswith('store') else 'load'),
              ('cycle_mod_II', start % max(P['II'], 1)), ('op', self.ref(i)),
              ('src_line', o['src'])
          ]))
    rows = collections.OrderedDict()
    for p in self.pipes:
      if pid is not None and p['id'] != pid:
        continue
      for r, raw in zip(self.mrt_rows(p), p['mrt']):
        if raw['m'] == key:
          rows['P%d' % p['id']] = r
    return collections.OrderedDict([('label', m['label']), ('ssa', m['ssa']),
                                    ('key', key), ('accesses', acc),
                                    ('mrt', rows)])

  def q_memref(self, name, pipeline=None):
    pid = self._pipe(pipeline) if pipeline is not None else None
    keys = [k for k, m in self.mem.items() if name in (k, m['label'], m['ssa'])]
    if not keys:
      raise QueryError(
          'no memref %r (have: %s)' %
          (name, ', '.join(sorted({m['label'] for m in self.mem.values()}))))
    return {'memrefs': [self._memref(k, pid) for k in keys]}

  def q_line(self, line):
    n = _to_int('line', line)
    if not 1 <= n <= len(self.src_lines):
      raise QueryError('line %d out of range 1..%d' % (n, len(self.src_lines)))
    fn = None
    for f in self.fns:
      if f['span'] and f['span'][0] <= n <= f['span'][1]:
        fn = f['name']
        break
    ids = self.line_ops.get(n, [])
    ops, more = _capped([self.brief(i, 160) for i in ids])
    out = collections.OrderedDict([
        ('line', n), ('text', self.src_lines[n - 1]), ('function', fn),
        ('stages',
         sorted({'P%d·S%d' % (self.ops[i]['p'], self.ops[i]['s']) for i in ids
                })), ('ops', ops)
    ])
    if more:
      out['ops_truncated'] = more
    return out

  def q_search(self, q, pipeline=None, limit=50):
    pid = self._pipe(pipeline) if pipeline is not None else None
    limit = _to_int('limit', limit)
    ql = str(q).lower()
    hits = [
        i for i in self._ops_in(pid, None)
        if ql in self.ops[i]['n'].lower() or ql in self.ops[i]['t'].lower()
    ]
    return {
        'query': q,
        'count': len(hits),
        'ops': [self.brief(i, 160) for i in hits[:limit]]
    }

  def q_cdfg(self, pipeline, stage=None, consts=False, max_lines=500):
    pid = self._pipe(pipeline)
    s = self._stage(pid, stage) if stage is not None else None
    consts = _flag(consts)
    P = self.pipes[pid]
    out = [
        '# P%d in %s: II=%s trip_count=%s depth=%d latency=%d' %
        (pid, self.fn_name(P['func']), P['II'], P['trip_count'], len(
            P['stages']), P['latency']),
        '# "#N" = op id. "<= %v<-#M kind+Hr" = operand %v comes from op #M over '
        'a comb/reg/carried edge crossing H stage registers.' +
        (' "=> #M" = consumers in other stages.' if s is not None else ''),
    ]
    for it in P['iter_args']:
      out.append('# iter_arg %s = %s, next = %s%s' %
                 (it['name'], it['init'], it['next'], ' from #%d' %
                  it['producer'] if it['producer'] is not None else ''))
    for k, S in enumerate(P['stages']):
      if s is not None and k != s:
        continue
      out.append(
          'S%d [%d,%d)%s' %
          (k, S['start'], S['end'], ' when ' + S['when'] if S['when'] else ''))
      hidden = 0
      for i in S['ops']:
        o = self.ops[i]
        if o['c'] == 'const' and not consts:
          hidden += 1
          continue
        line = '  #%d %s' % (i, _short(o['t'], 150))
        if o['src'] is not None:
          line += '  L%d' % o['src']
        ins = [
            '%s<-#%d %s%s' %
            (e['v'], e['f'], e['k'], '+%dr' % e['h'] if e['h'] else '')
            for e in self.in_edges[i]
        ]
        if ins:
          line += '  <= ' + ', '.join(ins)
        if s is not None:
          outs = sorted(
              {e['t'] for e in self.out_edges[i] if self.ops[e['t']]['s'] != k})
          if outs:
            line += '  => ' + ', '.join('#%d' % t for t in outs)
        out.append(line)
        if len(out) >= max_lines:
          out.append('... truncated; query single stages with --stage')
          return {'text': '\n'.join(out)}
      if hidden:
        out.append('  (%d constants hidden)' % hidden)
    return {'text': '\n'.join(out)}

  def q_ir(self, **kw):
    return self._lines(self.ir_lines, kw['from'], kw.get('to'),
                       'loopschedule IR')

  def q_src(self, **kw):
    return self._lines(self.src_lines, kw['from'], kw.get('to'), 'source')

  # ---- browser selection ----

  def context(self, sel):
    """Resolves a browser selection into the data an agent needs."""
    sel = sel or {}
    out = collections.OrderedDict()
    view = sel.get('preview') or sel.get('pinned')
    try:
      if view:
        pid, s = self._pipe(view['p']), None
        s = self._stage(pid, view['s'])
        out['viewing'] = 'P%d·S%d (%s)' % (pid, s, 'hover preview'
                                           if sel.get('preview') else 'pinned')
        out['pipeline'] = self.pipe_brief(pid)
        out['stage'] = self.q_stage(pid, s)
      if sel.get('op') is not None:
        out['focused_op'] = self.q_op(sel['op'])
      hov = sel.get('hover')
      if hov is not None and hov != sel.get('op'):
        out['hovered_op'] = self.brief(self._op(hov))
      if sel.get('value'):
        pid = view['p'] if view else None
        v = self.q_value(sel['value'], pid)
        if pid is not None and not (v.get('definitions') or v.get('uses') or
                                    v.get('memrefs') or v.get('source_lines')):
          v = self.q_value(sel['value'])
        out['selected_variable'] = v
      if sel.get('line'):
        out['source_line'] = self.q_line(sel['line'])
      if sel.get('fn') is not None and 0 <= sel['fn'] < len(self.fns):
        out['function'] = self.fns[sel['fn']]['name']
    except QueryError as e:
      out['error'] = str(e)
    return out


# ----------------------------------------------------------------------------
# Agent bridge
# ----------------------------------------------------------------------------

PROMPT = """You are answering a question from a hardware engineer who is looking \
at a loopschedule pipeline schedule in loopschedule-vis, an interactive viewer \
for the output of hls-est (a static BRAM/port estimator for FPGA HLS built on \
CIRCT; accuracy against Vitis HLS csynth matters).

Background:
- A loopschedule.pipeline has an initiation interval II, a trip count, and \
stages S0..Sn. Stage k covers cycles [start(k), start(k+1)); the last stage is \
1 cycle. Ops are numbered "op #N" globally.
- Dataflow edges: comb (producer in the same stage), reg (from an earlier \
stage through stage registers; reg_hops = registers crossed), carried (from \
the previous iteration via iter_args; lands at consumer start + II).
- The modulo reservation table (MRT) counts memory accesses per memref at \
(stage start mod II); more than 2 in a cycle exceeds a dual-port BRAM.

Kernel: {title}
Loopschedule IR: {ir}
Source (left pane): {source}

## What the user is looking at right now
{context}

## Querying for more
The viewer's JSON API is live at {base}. Use it (with curl, quoting the URL) \
instead of guessing, e.g.:
  curl -s "{base}/api/cdfg?pipeline=0&stage=2"
  curl -s "{base}/api/op?id=41"
  curl -s "{base}/api/value?name=%2512&pipeline=0"    (URL-encode % as %25)
  curl -s "{base}/api/value?name=A"
  curl -s "{base}/api/ir?from=100&to=140"
Commands: {commands}. GET {base}/api/help lists their parameters; \
{docs} documents them.

## How to answer
Be concrete and brief. Refer to ops as "op #N", stages as "P<p>·S<s>" and \
source lines as "L<n>": the viewer turns those into links. Use Markdown.

## Question
{question}
"""


class Agent:
  """Runs one agent process per question (prompt on stdin, answer on stdout).

  The default is `claude -p --output-format json`, resumed with --resume for
  follow-up questions so a conversation keeps its context.
  """

  def __init__(self, cmd, timeout, model, base, index, data):
    self.custom = shlex.split(cmd) if cmd else None
    self.exe = None if cmd else shutil.which('claude')
    self.available = bool(self.custom or self.exe)
    self.timeout = timeout
    self.model = model
    self.base = base
    self.index = index
    self.data = data

  def describe(self):
    if self.custom:
      return ' '.join(shlex.quote(c) for c in self.custom)
    return 'claude -p' if self.exe else None

  def command(self, session):
    if self.custom:
      return list(self.custom)
    cmd = [
        self.exe, '-p', '--output-format', 'json', '--allowedTools',
        'Bash(curl:*),Read,Grep,Glob'
    ]
    if self.model:
      cmd += ['--model', self.model]
    if session:
      cmd += ['--resume', session]
    return cmd

  def prompt(self, question, selection):
    ctx = self.index.context(selection)
    blocks = []
    for key, val in ctx.items():
      if key == 'stage':
        view = selection.get('preview') or selection.get('pinned')
        text = self.index.q_cdfg(view['p'], view['s'])['text']
        blocks.append('### stage (CDFG of the stage in view)\n' +
                      _short(text, MAX_CONTEXT))
        mem = val.get('memory')
        if mem:
          blocks.append(
              '### memory accesses in this stage (MRT column %d)\n%s' %
              (val['mrt_column'], json.dumps(mem)))
        continue
      text = val if isinstance(val, str) else json.dumps(
          val, indent=1, ensure_ascii=False)
      blocks.append('### %s\n%s' % (key, _short(text, MAX_CONTEXT)))
    if not blocks:
      blocks.append('(nothing selected; start from GET %s/api/summary)' %
                    self.base)
    d = self.data
    return PROMPT.format(title=d['title'],
                         ir=d['ir'] or d['input'],
                         source=d['source']['path'],
                         context='\n\n'.join(blocks),
                         base=self.base,
                         commands=', '.join(c for c in COMMANDS if c != 'ping'),
                         docs=AGENTS_DOC,
                         question=question.strip())

  def ask(self, question, selection, session=None):
    if not self.available:
      return {
          'error': 'no agent configured: `claude` is not on PATH; restart '
                   'with --agent-cmd'
      }
    prompt = self.prompt(question, selection)
    env = dict(os.environ)
    env[SERVER_ENV] = self.base
    t0 = time.time()
    try:
      proc = subprocess.run(self.command(session),
                            input=prompt,
                            stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE,
                            universal_newlines=True,
                            timeout=self.timeout,
                            cwd=REPO_ROOT,
                            env=env)
    except subprocess.TimeoutExpired:
      return {'error': 'agent timed out after %ds' % self.timeout}
    except OSError as e:
      return {'error': 'cannot run agent: %s' % e}
    out = proc.stdout.strip()
    answer, new_session, is_error = out, None, False
    try:
      j = json.loads(out)
      if isinstance(j, dict) and 'result' in j:
        answer = j.get('result') or ''
        new_session = j.get('session_id')
        is_error = bool(j.get('is_error'))
    except ValueError:
      pass
    res = {
        'answer': answer,
        'session': new_session,
        'seconds': round(time.time() - t0, 1)
    }
    if proc.returncode != 0 or is_error or not answer:
      res['error'] = 'agent exited with status %d%s' % (
          proc.returncode,
          ': ' + proc.stderr.strip()[-2000:] if proc.stderr.strip() else '')
    return res


# ----------------------------------------------------------------------------
# HTTP server
# ----------------------------------------------------------------------------


class Selection:

  def __init__(self):
    self.lock = threading.Lock()
    self.value = {}
    self.updated = None

  def set(self, value):
    with self.lock:
      self.value = value
      self.updated = time.time()

  def get(self):
    with self.lock:
      return dict(self.value), self.updated


def _clean_selection(body):
  """Keeps only the known selection fields, with the expected types."""
  out = {}
  for k in ('pinned', 'preview'):
    v = body.get(k)
    if isinstance(v, dict) and isinstance(v.get('p'), int) and isinstance(
        v.get('s'), int):
      out[k] = {'p': v['p'], 's': v['s']}
  for k in ('op', 'hover', 'line', 'fn'):
    if isinstance(body.get(k), int):
      out[k] = body[k]
  if isinstance(body.get('value'), str) and body['value'].strip():
    out['value'] = body['value'].strip()[:200]
  return out


def make_handler(index, html, agent, selection, allowed_hosts, verbose):

  class Handler(BaseHTTPRequestHandler):
    server_version = 'loopschedule-vis'

    def log_message(self, fmt, *args):
      if verbose:
        sys.stderr.write('loopschedule-vis: %s\n' % (fmt % args))

    def _send(self, code, body, ctype):
      data = body.encode('utf-8')
      self.send_response(code)
      self.send_header('Content-Type', ctype)
      self.send_header('Content-Length', str(len(data)))
      self.send_header('Cache-Control', 'no-store')
      self.send_header('X-Content-Type-Options', 'nosniff')
      self.end_headers()
      self.wfile.write(data)

    def _json(self, code, obj):
      self._send(code,
                 json.dumps(obj, indent=1, ensure_ascii=False) + '\n',
                 'application/json; charset=utf-8')

    def _host_ok(self):
      # Rejects DNS-rebinding requests addressed to another host name.
      return self.headers.get('Host', '') in allowed_hosts

    def _origin_ok(self):
      origin = self.headers.get('Origin')
      if not origin:
        return True
      return urllib.parse.urlparse(origin).netloc in allowed_hosts

    def do_GET(self):
      if not self._host_ok():
        return self._json(403, {'error': 'unexpected Host header'})
      url = urllib.parse.urlparse(self.path)
      path = url.path
      if path in ('/', '/index.html'):
        return self._send(200, html, 'text/html; charset=utf-8')
      if path in ('/AGENTS.md', '/api/docs'):
        try:
          with open(AGENTS_DOC, encoding='utf-8') as f:
            return self._send(200, f.read(), 'text/markdown; charset=utf-8')
        except OSError:
          return self._json(404, {'error': 'AGENTS.md not found'})
      if path.rstrip('/') == '/api':
        return self._json(200, help_text())
      if not path.startswith('/api/'):
        return self._json(404, {'error': 'not found; try /api/help'})
      parts = [urllib.parse.unquote(p) for p in path[5:].split('/') if p]
      cmd, positional = (parts[0] if parts else 'help'), parts[1:]
      params = {
          k: v[-1] for k, v in urllib.parse.parse_qs(
              url.query, keep_blank_values=True).items()
      }
      if cmd == 'ping':
        return self._json(
            200, {
                'ok': True,
                'title': index.data['title'],
                'agent': agent.describe() if agent and agent.available else None
            })
      if cmd == 'selection':
        sel, updated = selection.get()
        return self._json(
            200, {
                'selection':
                    sel,
                'updated':
                    updated,
                'age_seconds':
                    round(time.time() - updated, 1) if updated else None,
                'context':
                    index.context(sel)
            })
      try:
        return self._json(200, index.dispatch(cmd, params, positional))
      except QueryError as e:
        return self._json(400, {'error': str(e)})

    def do_POST(self):
      if not self._host_ok() or not self._origin_ok():
        return self._json(403, {'error': 'cross-origin request refused'})
      if not self.headers.get('Content-Type',
                              '').startswith('application/json'):
        return self._json(415, {'error': 'expected application/json'})
      try:
        n = int(self.headers.get('Content-Length', '0'))
        body = json.loads(self.rfile.read(min(n, 1 << 20)) or b'{}')
        if not isinstance(body, dict):
          raise ValueError
      except ValueError:
        return self._json(400, {'error': 'bad JSON body'})
      path = urllib.parse.urlparse(self.path).path
      if path == '/api/selection':
        selection.set(_clean_selection(body))
        return self._json(200, {'ok': True})
      if path == '/api/ask':
        q = body.get('question')
        if not isinstance(q, str) or not q.strip():
          return self._json(400, {'error': 'question is required'})
        sel = body.get('selection')
        sel = _clean_selection(sel) if isinstance(sel,
                                                  dict) else selection.get()[0]
        session = body.get('session')
        session = session if isinstance(session, str) and re.match(
            r'^[\w-]{1,100}$', session) else None
        if agent is None:
          return self._json(200, {'error': 'agent disabled (--no-agent)'})
        sys.stderr.write('loopschedule-vis: asking agent: %s\n' %
                         _short(' '.join(q.split()), 100))
        try:
          res = agent.ask(q, sel, session)
        except Exception as e:  # report instead of dropping the connection
          return self._json(500, {'error': 'agent bridge failed: %r' % e})
        sys.stderr.write(
            'loopschedule-vis: agent answered in %ss%s\n' %
            (res.get('seconds', '?'), ' (error)' if res.get('error') else ''))
        return self._json(200, res)
      return self._json(404, {'error': 'not found'})

  return Handler


def serve(data, ir_text, html, args):
  index = QueryIndex(data, ir_text)
  port = args.port
  host = args.host
  httpd = ThreadingHTTPServer((host, port), None)
  port = httpd.server_address[1]
  base = 'http://localhost:%d' % port
  allowed = {'localhost:%d' % port, '127.0.0.1:%d' % port, '[::1]:%d' % port}
  if host not in ('127.0.0.1', 'localhost', '::1', '0.0.0.0', ''):
    allowed.add('%s:%d' % (host, port))
  agent = None
  if not args.no_agent:
    agent = Agent(args.agent_cmd, args.agent_timeout, args.agent_model, base,
                  index, data)
  selection = Selection()
  httpd.RequestHandlerClass = make_handler(index, html, agent, selection,
                                           allowed, args.verbose)
  who = agent.describe() if agent and agent.available else (
      'none (claude not on PATH; use --agent-cmd)' if agent else 'disabled')
  sys.stderr.write('loopschedule-vis: serving %s at %s/  (API: %s/api/help, '
                   'agent: %s). Ctrl+C stops.\n' %
                   (data['title'], base, base, who))
  sys.stderr.flush()
  if args.port_file:
    with open(args.port_file, 'w') as f:
      f.write('%d\n' % port)
  try:
    httpd.serve_forever()
  except KeyboardInterrupt:
    pass
  finally:
    httpd.server_close()
  return 0


# ----------------------------------------------------------------------------
# `query` command line
# ----------------------------------------------------------------------------


def parse_query_tokens(tokens):
  """[cmd, pos..., --key value | --flag ...] -> (cmd, positional, params)."""
  if not tokens:
    raise QueryError('missing command; try "help"')
  cmd, rest = tokens[0], tokens[1:]
  if cmd not in COMMANDS:
    raise QueryError('unknown command %r; commands: %s' %
                     (cmd, ', '.join(COMMANDS)))
  positional, params = [], {}
  i = 0
  while i < len(rest):
    t = rest[i]
    if t.startswith('--') and len(t) > 2:
      key = t[2:]
      if '=' in key:
        key, val = key.split('=', 1)
      elif key == 'consts':
        val = '1'
      elif i + 1 < len(rest):
        i += 1
        val = rest[i]
      else:
        raise QueryError('--%s needs a value' % key)
      params[key] = val
    else:
      positional.append(t)
    i += 1
  return cmd, positional, params


def query_server(base, cmd, positional, params):
  path = '/'.join([cmd] + [urllib.parse.quote(p, safe='') for p in positional])
  url = base.rstrip('/') + '/api/' + path
  if params:
    url += '?' + urllib.parse.urlencode(params)
  try:
    with urllib.request.urlopen(url, timeout=60) as r:
      return json.loads(r.read().decode('utf-8'))
  except urllib.error.HTTPError as e:
    try:
      msg = json.loads(e.read().decode('utf-8')).get('error')
    except ValueError:
      msg = str(e)
    raise QueryError(msg)
  except urllib.error.URLError as e:
    raise QueryError('cannot reach %s: %s (is `loopschedule-vis serve` '
                     'running?)' % (base, e.reason))


def print_result(cmd, result):
  if cmd == 'cdfg' and isinstance(result, dict) and 'text' in result:
    print(result['text'])
  else:
    print(json.dumps(result, indent=1, ensure_ascii=False))
