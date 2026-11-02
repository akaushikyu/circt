#!/usr/bin/env python3
"""loopschedule-vis: render hls-est loopschedule pipelines as an interactive,
self-contained HTML timing diagram.

The input is textual MLIR containing `loopschedule.pipeline` ops (the output of
`--convert-affine-to-loopschedule`). With --run-hls-est the input is instead
affine/source MLIR which is lowered first by invoking hls-est.

Only the Python 3 standard library is used, so nothing in CIRCT needs to be
rebuilt to use or change this tool.
"""

import argparse
import collections
import json
import os
import re
import shlex
import shutil
import subprocess
import sys

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
REPO_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
TEMPLATE_PATH = os.path.join(SCRIPT_DIR, 'template.html')
DATA_PLACEHOLDER = '__LOOPSCHEDULE_DATA__'

DEFAULT_PIPELINE = ('--auto-pipeline-unroll --canonicalize --affine-scalrep '
                    '--affine-loop-normalize --memory-banking-bram '
                    '--convert-affine-to-loopschedule')
HLS_EST_CANDIDATES = ('build/bin/hls-est', 'bin/hls-est',
                      'build/clion/bin/hls-est')

KNOWN_LS_OPS = {
    'loopschedule.pipeline', 'loopschedule.pipeline.stage',
    'loopschedule.register', 'loopschedule.terminator'
}
LOOP_OP_RE = re.compile(r'^(affine|scf)\.(for|parallel|while)$')

SSA_NAME = r'%[A-Za-z0-9_.$-]+'
SSA_RE = re.compile(SSA_NAME + r'(?:#\d+)?')
HEAD_RE = re.compile(r'\s*(?:(?P<res>%[^=]*?)\s*=\s*)?'
                     r'(?P<name>"[^"]*"|[A-Za-z_][\w$.]*)')
RESULT_RE = re.compile(r'(' + SSA_NAME + r')(?::(\d+))?$')
ALIAS_RE = re.compile(r'#(loc\d*)\s*=\s*(.*)$')
LOC_TOKEN_RE = re.compile(
    r'"(?P<file>(?:[^"\\]|\\.)*)"\s*:\s*(?P<line>\d+)(?:\s*:\s*(?P<col>\d+))?'
    r'|(?P<alias>#loc\d*)(?![\w$.])')
MEMREF_RE = re.compile(r'(' + SSA_NAME + r'(?:#\d+)?)\s*\[')
VARNAME_RE = re.compile(r'polygeist\.varname\s*=\s*"([^"]*)"')

INT_OPS = {
    'addi', 'subi', 'muli', 'divsi', 'divui', 'remsi', 'remui', 'ceildivsi',
    'ceildivui', 'floordivsi', 'andi', 'ori', 'xori', 'shli', 'shrsi', 'shrui',
    'index_cast', 'index_castui', 'extsi', 'extui', 'trunci', 'maxsi', 'minsi',
    'maxui', 'minui'
}


class Diagnostics:

  def __init__(self, quiet=False):
    self.warnings = []
    self.quiet = quiet

  def warn(self, msg):
    self.warnings.append(msg)
    if not self.quiet:
      print('loopschedule-vis: warning: ' + msg, file=sys.stderr)


# ----------------------------------------------------------------------------
# Textual IR parsing
# ----------------------------------------------------------------------------


class Region:
  __slots__ = ('owner', 'parent', 'ops', 'defs')

  def __init__(self, owner, parent):
    self.owner = owner
    self.parent = parent
    self.ops = []
    self.defs = {}

  def lookup(self, name):
    region = self
    while region is not None:
      d = region.defs.get(name)
      if d is not None:
        return d
      region = region.parent
    return None


class Op:
  __slots__ = ('uid', 'name', 'ir_line', 'close_line', 'code', 'text',
               'results', 'operands', 'regions', 'parent', 'loc', 'floc',
               'inline_locs', 'region_args')

  def __init__(self, uid, name, ir_line, code, text, parent):
    self.uid = uid
    self.name = name
    self.ir_line = ir_line
    self.close_line = None
    self.code = code
    self.text = text
    self.results = []
    self.operands = []
    self.regions = []
    self.parent = parent
    self.loc = None
    self.floc = None
    self.inline_locs = []
    self.region_args = []  # [(ssa name, kind)] defined in each new region


def _skip_string(s, i):
  i += 1
  n = len(s)
  while i < n:
    c = s[i]
    if c == '\\':
      i += 2
      continue
    if c == '"':
      return i + 1
    i += 1
  return n


def _match_paren(s, i):
  """`s[i]` is '('; returns the index just past the matching ')'."""
  depth = 0
  n = len(s)
  while i < n:
    c = s[i]
    if c == '"':
      i = _skip_string(s, i)
      continue
    if c == '(':
      depth += 1
    elif c == ')':
      depth -= 1
      if depth == 0:
        return i + 1
    i += 1
  return n


def scan_line(line):
  """Splits a line into (code, text, locs).

  `code` has string literals replaced by "" and loc(...) removed, so braces and
  SSA names can be counted safely. `text` keeps strings but drops locations and
  collapses whitespace (for display). `locs` holds the inner text of every
  loc(...) on the line, in order.
  """
  code, text, locs = [], [], []
  i, n = 0, len(line)
  while i < n:
    c = line[i]
    if c == '"':
      j = _skip_string(line, i)
      code.append('""')
      text.append(line[i:j])
      i = j
      continue
    if (c == 'l' and line.startswith('loc(', i) and
        (i == 0 or not (line[i - 1].isalnum() or line[i - 1] in '_.$%#@'))):
      j = _match_paren(line, i + 3)
      locs.append(line[i + 4:j - 1])
      i = j
      continue
    if c == '/' and line.startswith('//', i):
      break
    code.append(c)
    text.append(c)
    i += 1
  return ''.join(code), ' '.join(''.join(text).split()), locs


def brace_net(code):
  return code.count('{') - code.count('}')


def expand_results(res):
  out = []
  if not res:
    return out
  for part in res.split(','):
    m = RESULT_RE.match(part.strip())
    if not m:
      continue
    if m.group(2) is not None:
      out.extend('%s#%d' % (m.group(1), k) for k in range(int(m.group(2))))
    else:
      out.append(m.group(1))
  return out


def region_args_of(op, code_after_name):
  """SSA values an op defines inside its regions (block arguments)."""
  args = []
  m = re.search(r'iter_args\(', code_after_name)
  if m:
    end = _match_paren(code_after_name, m.end() - 1)
    inner = code_after_name[m.end():end - 1]
    for k, am in enumerate(
        re.finditer(r'(' + SSA_NAME + r')\s*=\s*([^,]+)', inner)):
      args.append((am.group(1), ('iter', op, k, am.group(2).strip())))
  if op.name.endswith('func') or op.name.endswith('.func'):
    m = re.search(r'@(?:[\w$.-]+|"[^"]*")\s*\(', code_after_name)
    if m:
      end = _match_paren(code_after_name, m.end() - 1)
      names = re.findall(r'(' + SSA_NAME + r')\s*:',
                         code_after_name[m.end():end - 1])
      for k, name in enumerate(names):
        args.append((name, ('funcarg', op, k)))
  if LOOP_OP_RE.match(op.name):
    m = re.match(r'\s*(' + SSA_NAME + r')\s*=', code_after_name)
    if m:
      args.append((m.group(1), ('iv', op, 0)))
    else:
      m = re.match(r'\s*\(([^)]*)\)\s*=', code_after_name)
      if m:
        for k, name in enumerate(re.findall(SSA_NAME, m.group(1))):
          args.append((name, ('iv', op, k)))
  return args


class Module:

  def __init__(self):
    self.root = Region(None, None)
    self.aliases = {}
    self.ops = []
    self.lines = []


def parse_ir(text, diag):
  mod = Module()
  mod.lines = text.splitlines()
  cur = mod.root
  unknown_ls = collections.OrderedDict()

  def open_region(owner):
    region = Region(owner, owner.parent)
    owner.regions.append(region)
    for name, d in owner.region_args:
      region.defs[name] = d
    return region

  for ln, raw in enumerate(mod.lines, 1):
    s = raw.strip()
    if not s or s.startswith('//'):
      continue
    if s.startswith('#') and cur is mod.root:
      m = ALIAS_RE.match(s)
      if m:
        mod.aliases[m.group(1)] = m.group(2)
      continue
    code, text_, locs = scan_line(raw)
    cs = code.strip()
    if not cs:
      continue
    if cs.startswith('}'):
      owner = cur.owner
      if owner is None:
        diag.warn('line %d: unbalanced "}"' % ln)
        continue
      rest = cs[1:].strip()
      if brace_net(rest) > 0:  # `} do {`, `} else {`, `}, {`
        cur = open_region(owner)
      else:
        owner.close_line = ln
        owner.loc = locs[-1] if locs else None
        cur = owner.parent
      continue
    if cs.startswith('^'):  # block label: define its arguments
      for name in re.findall(r'(' + SSA_NAME + r')\s*:', code):
        cur.defs[name] = ('blockarg', cur.owner, 0)
      continue
    m = HEAD_RE.match(code)
    if not m:
      diag.warn('line %d: cannot parse operation: %s' % (ln, s[:120]))
      continue
    name = m.group('name')
    if name.startswith('"'):
      tm = re.match(r'\s*(?:%[^=]*?\s*=\s*)?"([^"]*)"', text_)
      name = tm.group(1) if tm else '<generic>'
    op = Op(len(mod.ops), name, ln, code.strip(), text_, cur)
    mod.ops.append(op)
    cur.ops.append(op)
    op.results = expand_results(m.group('res'))
    after = code[m.end():]
    op.operands = SSA_RE.findall(after)
    for k, r in enumerate(op.results):
      cur.defs[r] = ('op', op, k)
    if name.startswith('loopschedule.') and name not in KNOWN_LS_OPS:
      unknown_ls.setdefault(name, []).append(ln)
    net = brace_net(code)
    if net > 0:
      op.inline_locs = locs
      op.region_args = region_args_of(op, after)
      cur = open_region(op)
      if net > 1:
        diag.warn('line %d: more than one region opened on one line' % ln)
    else:
      op.loc = locs[-1] if locs else None
      op.inline_locs = locs[:-1]
  if cur is not mod.root:
    diag.warn('end of input reached inside the region of %s (line %d)' %
              (cur.owner.name, cur.owner.ir_line))
  for name, lines in unknown_ls.items():
    diag.warn('unrecognized loopschedule op %s (%d occurrence%s, first on '
              'line %d); shown as "other"' %
              (name, len(lines), '' if len(lines) == 1 else 's', lines[0]))
  return mod


class LocResolver:
  """Resolves loc(...) text to the first FileLineCol, following #loc aliases
  and descending through fused/callsite/name locations in textual order."""

  def __init__(self, aliases):
    self.aliases = aliases
    self.cache = {}

  def resolve(self, text, depth=0):
    if not text or depth > 64:
      return None
    for m in LOC_TOKEN_RE.finditer(text):
      if m.group('file') is not None:
        f = m.group('file').replace('\\"', '"').replace('\\\\', '\\')
        return (f, int(m.group('line')), int(m.group('col') or 0))
      alias = m.group('alias')[1:]
      if alias in self.cache:
        r = self.cache[alias]
      else:
        self.cache[alias] = None  # guard against cycles
        r = self.resolve(self.aliases.get(alias), depth + 1)
        self.cache[alias] = r
      if r:
        return r
    return None


def walk(region):
  for op in region.ops:
    yield op
    for r in op.regions:
      yield from walk(r)


def ancestors(op):
  region = op.parent
  while region is not None and region.owner is not None:
    yield region.owner
    region = region.parent


# ----------------------------------------------------------------------------
# Value resolution through pipeline stage registers
# ----------------------------------------------------------------------------


class ValueResolver:
  """Maps an SSA use to its original producer.

  Returns (kind, payload, hops). kind is 'op' (payload = producing Op),
  'iter'/'funcarg'/'iv'/'blockarg' (payload = the def tuple), or 'unknown'.
  hops counts the stage registers the value passed through.
  """

  def __init__(self):
    self.memo = {}

  def value(self, tok, region):
    d = region.lookup(tok)
    if d is None:
      return ('unknown', tok, 0)
    if d[0] != 'op':
      return (d[0], d, 0)
    op, idx = d[1], d[2]
    if op.name != 'loopschedule.pipeline.stage':
      return ('op', op, 0)
    key = (op.uid, idx)
    if key in self.memo:
      return self.memo[key]
    self.memo[key] = ('unknown', tok, 0)  # guard against cycles
    reg = stage_register(op)
    if reg is None or idx >= len(reg.operands):
      r = ('unknown', tok, 0)
    else:
      k, payload, hops = self.value(reg.operands[idx], reg.parent)
      r = (k, payload, hops + 1)
    self.memo[key] = r
    return r


def stage_register(stage):
  if not stage.regions or not stage.regions[0].ops:
    return None
  last = stage.regions[0].ops[-1]
  return last if last.name == 'loopschedule.register' else None


def categorize(name):
  short = name.rsplit('.', 1)[-1]
  if short in ('load', 'store'):
    return 'memory'
  if short in ('mulf', 'divf', 'remf', 'fma'):
    return 'fmul'
  if short in ('addf', 'subf', 'negf'):
    return 'fadd'
  if short in ('cmpi', 'cmpf', 'select'):
    return 'cmp'
  if short == 'constant':
    return 'const'
  if ((name.startswith('arith.') and short in INT_OPS) or
      name.startswith('index.') or
      name in ('affine.apply', 'affine.min', 'affine.max')):
    return 'int'
  return 'other'


# ----------------------------------------------------------------------------
# Source resolution
# ----------------------------------------------------------------------------


def _dir_chain(path):
  out = []
  d = os.path.abspath(path)
  while True:
    out.append(d)
    parent = os.path.dirname(d)
    if parent == d:
      return out
    d = parent


def find_file(fname, bases):
  if os.path.isabs(fname):
    return fname if os.path.isfile(fname) else None
  for b in bases:
    p = os.path.normpath(os.path.join(b, fname))
    if os.path.isfile(p):
      return p
  return None


def lang_of(path):
  ext = os.path.splitext(path)[1].lower()
  if ext == '.mlir':
    return 'mlir'
  return 'c'


def brace_span(lines, start):
  """Brace-matches from 1-based line `start`; returns (start, end) or None.
  Gives up if a ';' ends a statement before the first '{' (a prototype or a
  call rather than a definition)."""
  depth = 0
  seen = False
  in_block = False
  for ln in range(start, len(lines) + 1):
    s = lines[ln - 1]
    i, n = 0, len(s)
    while i < n:
      if in_block:
        j = s.find('*/', i)
        if j < 0:
          break
        in_block = False
        i = j + 2
        continue
      c = s[i]
      if c == '/' and s.startswith('//', i):
        break
      if c == '/' and s.startswith('/*', i):
        in_block = True
        i += 2
        continue
      if c in '"\'':
        q = c
        i += 1
        while i < n and s[i] != q:
          i += 2 if s[i] == '\\' else 1
        i += 1
        continue
      if c == '{':
        depth += 1
        seen = True
      elif c == '}':
        depth -= 1
        if seen and depth == 0:
          return (start, ln)
      elif c == ';' and not seen:
        return None
      i += 1
    if not seen and ln - start > 40:
      return None
  return None


def find_function_span(lines, lang, name, hint_line):
  if hint_line:
    span = brace_span(lines, hint_line)
    if span:
      return span
  if lang == 'mlir':
    pat = re.compile(r'func\.func\s+(?:\w+\s+)?@' + re.escape(name) + r'\s*\(')
  else:
    pat = re.compile(r'(?<![\w.>])' + re.escape(name) + r'\s*\(')
  for i, s in enumerate(lines, 1):
    if pat.search(s):
      span = brace_span(lines, i)
      if span:
        return span
  return None


def param_name(line_text, col):
  seg = line_text[col - 1:] if col > 0 else line_text
  m = re.match(SSA_NAME, seg)
  if m:
    return m.group(0)
  depth = 0
  end = len(seg)
  for i, c in enumerate(seg):
    if c in '([':
      depth += 1
    elif c in ')]':
      if depth == 0:
        end = i
        break
      depth -= 1
    elif c == ',' and depth == 0:
      end = i
      break
  decl = re.sub(r'\[[^\]]*\]', '', seg[:end])
  ids = re.findall(r'[A-Za-z_]\w*', decl)
  return ids[-1] if ids else None


# ----------------------------------------------------------------------------
# Schedule extraction
# ----------------------------------------------------------------------------


def int_attr(pattern, text):
  m = re.search(pattern, text)
  return int(m.group(1)) if m else None


def short_text(text, limit=600):
  return text if len(text) <= limit else text[:limit] + ' …'


class Builder:

  def __init__(self, mod, diag, source):
    self.mod = mod
    self.diag = diag
    self.source = source  # dict with mode/path/lines and a src_of(op) hook
    self.values = ValueResolver()
    self.ops = []
    self.io = []  # per op: full result and operand lists (for queries)
    self.op_id = {}
    self.memrefs = collections.OrderedDict()
    self.functions = []
    self.pipelines = []
    self.func_args = {}  # func op uid -> {ssa: C name}

  def memref_of(self, op):
    m = MEMREF_RE.search(op.code)
    if not m:
      return None
    tok = m.group(1)
    kind, payload, _ = self.values.value(tok, op.parent)
    if kind == 'op':
      key = 'op%d' % payload.uid
      vm = VARNAME_RE.search(payload.text)
      ssa = payload.results[0] if payload.results else tok
      label = vm.group(1) if vm else ssa
    elif kind == 'funcarg':
      fop, k = payload[1], payload[2]
      key = 'fa%d_%d' % (fop.uid, k)
      ssa = fop.region_args[k][0] if k < len(fop.region_args) else tok
      cname = self.func_args.get(fop.uid, {}).get(ssa)
      label = cname if cname else ssa
    else:
      key = 'tok:' + tok
      ssa = label = tok
    if key not in self.memrefs:
      self.memrefs[key] = {'label': label, 'ssa': ssa}
    return key

  def add_function(self, fop):
    m = re.search(r'@([\w$.-]+|"[^"]*")', fop.code)
    name = m.group(1).strip('"') if m else '<anon>'
    src = self.source
    args = {}
    fargs = [a for a in fop.region_args if a[1][0] == 'funcarg']
    if src['mode'] != 'ir' and len(fop.inline_locs) == len(fargs):
      for (ssa, _), loc_text in zip(fargs, fop.inline_locs):
        floc = src['resolver'].resolve(loc_text)
        line = src['line_of'](floc)
        if line and line <= len(src['lines']):
          pname = param_name(src['lines'][line - 1], floc[2])
          if pname:
            args[ssa] = pname
    self.func_args[fop.uid] = args
    if src['mode'] == 'ir':
      span = [fop.ir_line, fop.close_line or fop.ir_line]
      line = fop.ir_line
    else:
      line = src['line_of'](fop.floc)
      sp = find_function_span(src['lines'], src['lang'], name, line)
      span = list(sp) if sp else None
      if line is None and sp:
        line = sp[0]
    f = {
        'id': len(self.functions),
        'name': name,
        'line': line,
        'span': span,
        'ir_line': fop.ir_line,
        'args': args,
        'pipelines': []
    }
    self.functions.append(f)
    return f

  def add_pipeline(self, pop, fn):
    diag = self.diag
    II = int_attr(r'\bII\s*=\s*(-?\d+)', pop.code)
    trip = int_attr(r'\btrip_count\s*=\s*(-?\d+)', pop.code)
    if II is None:
      diag.warn('line %d: pipeline without II' % pop.ir_line)
      II = 1
    if len(pop.regions) != 2:
      diag.warn('line %d: expected 2 regions on loopschedule.pipeline, found '
                '%d; skipped' % (pop.ir_line, len(pop.regions)))
      return
    stages_region = pop.regions[1]
    stages, term = [], None
    for o in stages_region.ops:
      if o.name == 'loopschedule.pipeline.stage':
        stages.append(o)
      elif o.name == 'loopschedule.terminator':
        term = o
      else:
        diag.warn('line %d: unexpected %s in pipeline stages region' %
                  (o.ir_line, o.name))
    pid = len(self.pipelines)
    src_of = self.source['src_of']

    # Stages and their cycle spans.
    starts = []
    for k, st in enumerate(stages):
      start = int_attr(r'\bstart\s*=\s*(-?\d+)', st.code)
      if start is None:
        diag.warn('line %d: stage without start' % st.ir_line)
        start = starts[-1] + 1 if starts else 0
      if starts and start <= starts[-1]:
        diag.warn('line %d: stage start %d is not after previous start %d' %
                  (st.ir_line, start, starts[-1]))
      starts.append(start)
    stage_json = []
    op_stage = {}
    for k, st in enumerate(stages):
      end = starts[k + 1] if k + 1 < len(stages) else starts[k] + 1
      if end <= starts[k]:
        end = starts[k] + 1
      reg = stage_register(st)
      if reg is None:
        diag.warn('line %d: stage without loopschedule.register terminator' %
                  st.ir_line)
      when = re.search(r'\bwhen\s+(' + SSA_NAME + r'(?:#\d+)?)', st.code)
      ids = []
      for o in walk(st.regions[0]) if st.regions else ():
        if o is reg:
          continue
        oid = len(self.ops)
        self.op_id[o.uid] = oid
        op_stage[o.uid] = k
        cat = categorize(o.name)
        results = ', '.join(o.results[:3])
        if len(o.results) > 3:
          results += ' …'
        self.ops.append({
            'id': oid,
            'n': o.name,
            't': short_text(o.text),
            'r': results,
            'p': pid,
            's': k,
            'src': src_of(o),
            'ir': o.ir_line,
            'c': cat,
            'm': self.memref_of(o) if cat == 'memory' else None,
        })
        self.io.append({'results': o.results, 'operands': o.operands})
        ids.append(oid)
      stage_json.append({
          'start': starts[k],
          'end': end,
          'ir_line': st.ir_line,
          'when': when.group(1) if when else None,
          'ops': ids,
          'regs': len(reg.operands) if reg else 0,
      })

    # Terminator operands.
    term_iters, term_results = [], []
    if term is None:
      diag.warn('line %d: pipeline without loopschedule.terminator' %
                pop.ir_line)
    else:
      m = re.search(r'iter_args\(([^)]*)\)', term.code)
      term_iters = SSA_RE.findall(m.group(1)) if m else []
      m = re.search(r'results\(([^)]*)\)', term.code)
      term_results = SSA_RE.findall(m.group(1)) if m else []

    iter_defs = [a for a in pop.region_args if a[1][0] == 'iter']
    if term and len(term_iters) != len(iter_defs):
      diag.warn('line %d: terminator has %d iter_args but pipeline has %d' %
                (term.ir_line, len(term_iters), len(iter_defs)))
    iter_json = []
    for k, (name, d) in enumerate(iter_defs):
      nxt = term_iters[k] if k < len(term_iters) else None
      prod = None
      hops = 0
      if nxt:
        kind, payload, hops = self.values.value(nxt, stages_region)
        if kind == 'op' and payload.uid in op_stage:
          prod = self.op_id[payload.uid]
      iter_json.append({
          'name': name,
          'init': d[3],
          'next': nxt,
          'producer': prod,
          'hops': hops
      })

    # Dataflow edges.
    edges = []
    seen = set()

    def add_edge(f, t, kind, hops, value):
      key = (f, t, kind)
      if key in seen:
        return
      seen.add(key)
      edges.append({'f': f, 't': t, 'k': kind, 'h': hops, 'v': value})

    for o_uid, cs in op_stage.items():
      o = self.mod.ops[o_uid]
      cid = self.op_id[o_uid]
      for tok in o.operands:
        kind, payload, hops = self.values.value(tok, o.parent)
        if kind == 'op':
          if payload.uid not in op_stage:
            continue  # defined outside the pipeline (e.g. a constant)
          ps = op_stage[payload.uid]
          if ps == cs:
            add_edge(self.op_id[payload.uid], cid, 'comb', hops, tok)
          elif ps < cs:
            add_edge(self.op_id[payload.uid], cid, 'reg', hops, tok)
          else:
            diag.warn('line %d: %s uses %s produced in a later stage' %
                      (o.ir_line, o.name, tok))
        elif kind == 'iter' and payload[1] is pop:
          it = iter_json[payload[2]] if payload[2] < len(iter_json) else None
          if it and it['producer'] is not None:
            add_edge(it['producer'], cid, 'carried', it['hops'], tok)

    # Modulo reservation table: memory accesses at (start mod II).
    mrt = collections.OrderedDict()
    period = max(II, 1)
    for k, sj in enumerate(stage_json):
      col = sj['start'] % period
      for oid in sj['ops']:
        opj = self.ops[oid]
        if opj['m'] is None:
          continue
        row = mrt.setdefault(opj['m'], {
            'm': opj['m'],
            'loads': [0] * period,
            'stores': [0] * period
        })
        is_store = opj['n'].endswith('store')
        row['stores' if is_store else 'loads'][col] += 1

    nest = []
    for anc in ancestors(pop):
      if LOOP_OP_RE.match(anc.name):
        nest.append({
            'op': anc.name,
            'text': short_text(anc.text, 160),
            'src': src_of(anc),
            'ir': anc.ir_line
        })
    nest.reverse()

    latency = 0
    if stage_json:
      latency = stage_json[-1]['end'] - stage_json[0]['start']
    self.pipelines.append({
        'id': pid,
        'func': fn['id'] if fn else None,
        'II': II,
        'trip_count': trip,
        'ir_line': pop.ir_line,
        'src': src_of(pop),
        'results': pop.results,
        'term_results': term_results,
        'nest': nest,
        'iter_args': iter_json,
        'stages': stage_json,
        'latency': latency,
        'edges': edges,
        'mrt': list(mrt.values()),
    })
    if fn:
      fn['pipelines'].append(pid)

  def run(self):
    fn_of = {}
    for op in self.mod.ops:
      if op.name == 'func.func' or op.name.endswith('.func'):
        if op.regions:  # skip external declarations
          fn_of[op.uid] = self.add_function(op)
    for op in self.mod.ops:
      if op.name != 'loopschedule.pipeline':
        continue
      fn = None
      for anc in ancestors(op):
        if anc.uid in fn_of:
          fn = fn_of[anc.uid]
          break
      if fn is None:
        if '<module>' not in fn_of:
          fn_of['<module>'] = {
              'id': len(self.functions),
              'name': '<module>',
              'line': None,
              'span': None,
              'ir_line': None,
              'args': {},
              'pipelines': []
          }
          self.functions.append(fn_of['<module>'])
        fn = fn_of['<module>']
      self.add_pipeline(op, fn)


def setup_source(mod, resolver, ir_path, ir_text, args, input_mlir, diag):
  """Picks the source shown on the left and how op locations map onto it."""
  bases = [os.getcwd(), os.path.dirname(os.path.abspath(ir_path))]
  if input_mlir:
    bases.append(os.path.dirname(os.path.abspath(input_mlir)))
  bases += _dir_chain(os.path.dirname(os.path.abspath(ir_path)))
  bases.append(REPO_ROOT)

  for op in mod.ops:
    op.floc = resolver.resolve(op.loc)

  counts = collections.Counter()
  for op in mod.ops:
    if op.floc:
      counts[op.floc[0]] += 1
    for loc_text in op.inline_locs:
      r = resolver.resolve(loc_text)
      if r:
        counts[r[0]] += 1

  path, mode = None, None
  if args.source:
    if not os.path.isfile(args.source):
      raise SystemExit('loopschedule-vis: error: --source %s not found' %
                       args.source)
    path, mode = os.path.abspath(args.source), 'arg'
  else:
    for fname, _ in counts.most_common():
      p = find_file(fname, bases)
      if p:
        path, mode = p, 'loc'
        break
      diag.warn('location file %s not found on disk' % fname)
      break
    if path is None and input_mlir:
      path, mode = os.path.abspath(input_mlir), 'input'

  src = {'resolver': resolver}
  if path is None:
    src.update(mode='ir',
               path=os.path.abspath(ir_path),
               lang='mlir',
               lines=ir_text.splitlines())
    src['line_of'] = lambda floc: None
    src['src_of'] = lambda op: op.ir_line
    return src

  with open(path, encoding='utf-8', errors='replace') as f:
    lines = f.read().splitlines()
  match_cache = {}
  base = os.path.basename(path)

  def file_matches(fname):
    r = match_cache.get(fname)
    if r is None:
      p = find_file(fname, bases)
      r = bool(p and
               os.path.samefile(p, path)) or os.path.basename(fname) == base
      match_cache[fname] = r
    return r

  def line_of(floc):
    if floc and file_matches(floc[0]) and 0 < floc[1] <= len(lines):
      return floc[1]
    return None

  src.update(mode=mode, path=path, lang=lang_of(path), lines=lines)
  src['line_of'] = line_of
  src['src_of'] = lambda op: line_of(op.floc)
  return src


# ----------------------------------------------------------------------------
# Driver
# ----------------------------------------------------------------------------


def find_hls_est(explicit):
  if explicit:
    return explicit
  env = os.environ.get('HLS_EST')
  if env:
    return env
  for rel in HLS_EST_CANDIDATES:
    p = os.path.join(REPO_ROOT, rel)
    if os.path.isfile(p) and os.access(p, os.X_OK):
      return p
  found = shutil.which('hls-est')
  if found:
    return found
  raise SystemExit('loopschedule-vis: error: hls-est not found (tried %s under '
                   '%s and $PATH); pass --hls-est' %
                   (', '.join(HLS_EST_CANDIDATES), REPO_ROOT))


def run_hls_est(input_path, hls, pipeline):
  flags = shlex.split(pipeline)
  if '--mlir-print-debuginfo' not in flags:
    flags.append('--mlir-print-debuginfo')
  cmd = [hls, input_path] + flags
  print('loopschedule-vis: running ' + ' '.join(shlex.quote(c) for c in cmd),
        file=sys.stderr)
  proc = subprocess.run(cmd,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE,
                        universal_newlines=True)
  if proc.returncode != 0:
    sys.stderr.write(proc.stderr)
    raise SystemExit('loopschedule-vis: error: hls-est exited with status %d' %
                     proc.returncode)
  return proc.stdout


def build_data(ir_path, ir_text, args, input_mlir, diag):
  mod = parse_ir(ir_text, diag)
  resolver = LocResolver(mod.aliases)
  src = setup_source(mod, resolver, ir_path, ir_text, args, input_mlir, diag)
  b = Builder(mod, diag, src)
  b.run()
  if not b.pipelines:
    diag.warn('no loopschedule.pipeline ops found in %s' % ir_path)
  return {
      'version': 1,
      'title': args.title or os.path.basename(input_mlir or ir_path),
      'input': os.path.abspath(input_mlir or ir_path),
      'ir': None if input_mlir else os.path.abspath(ir_path),
      'pipeline_flags': args.pipeline if input_mlir else None,
      'source': {
          'path': src['path'],
          'mode': src['mode'],
          'lang': src['lang'],
          'lines': src['lines'],
      },
      'functions': b.functions,
      'pipelines': b.pipelines,
      'ops': b.ops,
      'memrefs': b.memrefs,
      'warnings': diag.warnings,
      'io': b.io,
  }


def render_html(data):
  with open(TEMPLATE_PATH, encoding='utf-8') as f:
    template = f.read()
  if DATA_PLACEHOLDER not in template:
    raise SystemExit('loopschedule-vis: error: %s lacks the %s placeholder' %
                     (TEMPLATE_PATH, DATA_PLACEHOLDER))
  # 'io' only serves queries (see loopschedule_api.py); keep the page small.
  data = {k: v for k, v in data.items() if k != 'io'}
  payload = json.dumps(data, separators=(',', ':'), ensure_ascii=False)
  # Keep `</script>` and `<!--` out of the inline JSON.
  payload = payload.replace('<', '\\u003c')
  return template.replace(DATA_PLACEHOLDER, payload, 1)


def add_input_args(p):
  """Options that pick and lower the input; shared by all modes."""
  p.add_argument('--source',
                 help='source file (.c or .mlir) to show next to the schedule')
  p.add_argument('--run-hls-est',
                 action='store_true',
                 help='lower the input with hls-est first')
  p.add_argument('--hls-est', help='path to hls-est (default: search)')
  p.add_argument(
      '--pipeline',
      default=DEFAULT_PIPELINE,
      help='hls-est flags used with --run-hls-est (default: %(default)s)')
  p.add_argument('--save-ir', help='with --run-hls-est, also save lowered IR')
  p.add_argument('--title', help='page title (default: input file name)')


def load_input(args, diag):
  """Returns (data, ir_text) for args.input."""
  if not os.path.isfile(args.input):
    raise SystemExit('loopschedule-vis: error: %s not found' % args.input)
  input_mlir = None
  if args.run_hls_est:
    input_mlir = args.input
    ir_text = run_hls_est(args.input, find_hls_est(args.hls_est), args.pipeline)
    ir_path = args.save_ir or args.input
    if args.save_ir:
      with open(args.save_ir, 'w', encoding='utf-8') as f:
        f.write(ir_text)
  else:
    ir_path = args.input
    with open(ir_path, encoding='utf-8', errors='replace') as f:
      ir_text = f.read()
  return build_data(ir_path, ir_text, args, input_mlir, diag), ir_text


def main_serve(argv):
  import loopschedule_api as api
  p = argparse.ArgumentParser(
      prog='loopschedule-vis serve',
      description='Serve the page over HTTP with a JSON query API and an '
      '"Ask agent" panel. See AGENTS.md.')
  p.add_argument('input',
                 help='loopschedule IR (or affine MLIR with --run-hls-est)')
  add_input_args(p)
  p.add_argument('--host',
                 default='127.0.0.1',
                 help='address to bind (default: %(default)s)')
  p.add_argument('--port',
                 type=int,
                 default=api.DEFAULT_PORT,
                 help='port (default: %(default)s; 0 picks a free one)')
  p.add_argument('--port-file', help='write the bound port to this file')
  p.add_argument('--agent-cmd',
                 help='agent command; the prompt is sent on stdin and the '
                 'answer read from stdout (default: claude -p)')
  p.add_argument('--agent-model', help='model passed to claude --model')
  p.add_argument('--agent-timeout',
                 type=int,
                 default=600,
                 help='seconds per question (default: %(default)s)')
  p.add_argument('--no-agent',
                 action='store_true',
                 help='serve the API without the agent bridge')
  p.add_argument('-v', '--verbose', action='store_true', help='log requests')
  args = p.parse_args(argv)
  diag = Diagnostics()
  data, ir_text = load_input(args, diag)
  return api.serve(data, ir_text, render_html(data), args)


def main_query(argv):
  import loopschedule_api as api
  p = argparse.ArgumentParser(
      prog='loopschedule-vis query',
      allow_abbrev=False,  # --p/--s after the command are query params
      usage='loopschedule-vis query [options] (<input> | --server URL) '
      '<command> [args] [--param value]',
      description='Answer one query about a schedule, as JSON (cdfg prints '
      'text). Commands: %s. Run "query <input> help" or see AGENTS.md.' %
      ', '.join(api.COMMANDS),
      epilog='Without an input, the server in --server or $%s is queried '
      '(needed for "selection").' % api.SERVER_ENV)
  p.add_argument('--server',
                 help='query a running `loopschedule-vis serve` instead of '
                 'parsing a file, e.g. http://localhost:%d' % api.DEFAULT_PORT)
  add_input_args(p)
  p.add_argument('rest',
                 nargs=argparse.REMAINDER,
                 help='[<input>] <command> [args]')
  args = p.parse_args(argv)
  rest = args.rest
  server = args.server
  if not server and rest and rest[0] in api.COMMANDS and not os.path.isfile(
      rest[0]):
    server = os.environ.get(api.SERVER_ENV)
    if not server:
      p.error('no input file and no --server (or $%s)' % api.SERVER_ENV)
  try:
    if server:
      cmd, positional, params = api.parse_query_tokens(rest)
      result = api.query_server(server, cmd, positional, params)
    else:
      if not rest:
        p.error('missing input')
      args.input = rest[0]
      cmd, positional, params = api.parse_query_tokens(rest[1:])
      if args.input.endswith('.json'):
        with open(args.input, encoding='utf-8') as f:
          data, ir_text = json.load(f), None
      else:
        data, ir_text = load_input(args, Diagnostics(quiet=True))
      result = api.QueryIndex(data, ir_text).dispatch(cmd, params, positional)
  except api.QueryError as e:
    print('loopschedule-vis query: error: %s' % e, file=sys.stderr)
    return 1
  api.print_result(cmd, result)
  return 0


def main(argv=None):
  sys.setrecursionlimit(max(sys.getrecursionlimit(), 20000))
  argv = sys.argv[1:] if argv is None else argv
  if argv and argv[0] == 'serve':
    return main_serve(argv[1:])
  if argv and argv[0] == 'query':
    return main_query(argv[1:])
  p = argparse.ArgumentParser(
      prog='loopschedule-vis',
      description='Visualize loopschedule pipeline schedules as an offline '
      'HTML timing diagram. Also: "loopschedule-vis serve ..." (page + query '
      'API + agent) and "loopschedule-vis query ..." (one query); see '
      'AGENTS.md.')
  p.add_argument('input',
                 help='loopschedule IR (or affine MLIR with --run-hls-est)')
  p.add_argument('-o', '--output', help='output HTML (default: <input>.html)')
  add_input_args(p)
  p.add_argument('--json', help='also write the extracted schedule as JSON')
  p.add_argument('--werror',
                 action='store_true',
                 help='exit with status 2 if any warning was emitted')
  p.add_argument('-q', '--quiet', action='store_true', help='no summary line')
  args = p.parse_args(argv)

  diag = Diagnostics()
  data, _ = load_input(args, diag)
  out = args.output or (os.path.splitext(os.path.basename(args.input))[0] +
                        '.html')
  html = render_html(data)
  with open(out, 'w', encoding='utf-8') as f:
    f.write(html)
  if args.json:
    with open(args.json, 'w', encoding='utf-8') as f:
      json.dump(data, f, indent=1)
  if not args.quiet:
    nstages = sum(len(pl['stages']) for pl in data['pipelines'])
    nedges = sum(len(pl['edges']) for pl in data['pipelines'])
    print(
        'loopschedule-vis: %s: %d function(s), %d pipeline(s), %d stages, '
        '%d ops, %d edges, source=%s (%s), %d warning(s) -> %s' %
        (data['title'], len(data['functions']), len(data['pipelines']), nstages,
         len(data['ops']), nedges, os.path.relpath(data['source']['path']),
         data['source']['mode'], len(diag.warnings), out),
        file=sys.stderr)
  if args.werror and diag.warnings:
    return 2
  return 0


if __name__ == '__main__':
  sys.exit(main())
