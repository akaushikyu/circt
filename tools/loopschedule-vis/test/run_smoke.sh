#!/usr/bin/env bash
# Smoke test for loopschedule-vis: regenerates HTML for every test input and
# fails on any error. Polybench inputs must convert without warnings;
# synthetic*.mlir inputs are allowed (and, for the unrecognized op, required)
# to warn, and their dataflow is checked against hand-derived expectations.
#
# Usage: test/run_smoke.sh [--run-hls-est]
#   --run-hls-est  also lower one polybench kernel through hls-est (needs the
#                  hls-est binary; skipped with a note if it is not found).
#   OUT_DIR=...    where to write HTML/JSON/logs (default: test/out).
set -uo pipefail

here=$(cd "$(dirname "$0")" && pwd)
tool_dir=$(dirname "$here")
tool="$tool_dir/loopschedule-vis"
out="${OUT_DIR:-$here/out}"
mkdir -p "$out"
fail=0

check_json() {
  python3 - "$@" <<'EOF'
import json, sys
path, name = sys.argv[1], sys.argv[2]
d = json.load(open(path))
assert d['pipelines'], 'no pipelines'
assert d['ops'], 'no ops'
for p in d['pipelines']:
  assert p['stages'], 'P%d has no stages' % p['id']
  assert p['II'] >= 1, 'P%d has II < 1' % p['id']
  for s in p['stages']:
    assert s['end'] > s['start'], 'P%d: empty stage span' % p['id']
  for e in p['edges']:
    assert e['k'] in ('comb', 'reg', 'carried'), e
ops = d['ops']
if name.startswith('synthetic'):
  (p,) = d['pipelines']
  def op(n, s):
    (o,) = [o for o in ops if o['n'] == n and o['s'] == s]
    return o['id']
  kinds = {}
  for e in p['edges']:
    kinds[(e['f'], e['t'], e['k'])] = e['h']
  ld0 = [o['id'] for o in ops if o['n'] == 'memref.load']
  addi, mulf, addf = op('arith.addi', 0), op('arith.mulf', 1), op('arith.addf', 2)
  muli, cmp1, cmp2 = op('arith.muli', 2), op('arith.cmpi', 1), op('arith.cmpi', 2)
  frob, sif = op('loopschedule.frobnicate', 1), op('scf.if', 2)
  want = {
    (mulf, frob, 'comb'): 0, (muli, cmp2, 'comb'): 0, (cmp2, sif, 'comb'): 0,
    (ld0[0], mulf, 'reg'): 1, (ld0[1], mulf, 'reg'): 1, (addi, cmp1, 'reg'): 1,
    (mulf, addf, 'reg'): 1, (addi, muli, 'reg'): 2,
    (addi, ld0[0], 'carried'): 1, (addi, ld0[1], 'carried'): 1,
    (addi, addi, 'carried'): 1, (addf, addf, 'carried'): 1,
  }
  assert kinds == want, 'edges differ:\n got %r\nwant %r' % (sorted(kinds.items()), sorted(want.items()))
  assert [(s['start'], s['end']) for s in p['stages']] == [(0, 1), (1, 3), (3, 4)]
  assert p['II'] == 1 and p['trip_count'] == 16 and p['src'] == 3
  assert d['source']['mode'] == 'loc' and d['source']['path'].endswith('synthetic.c')
  (f,) = d['functions']
  assert f['span'] == [1, 9], f['span']
  assert f['args'] == {'%arg0': 'a', '%arg1': 'b'}, f['args']
  assert ops[addf]['src'] == 6 and ops[mulf]['src'] == 5 and ops[cmp1]['src'] is None
  labels = sorted(d['memrefs'][r['m']]['label'] for r in p['mrt'])
  assert labels == ['a', 'b'], labels
  assert all(r['loads'] == [1] for r in p['mrt'])
EOF
}

run_one() {
  local name=$1; shift
  local log="$out/$name.log"
  if ! "$tool" "$@" -o "$out/$name.html" --json "$out/$name.json" 2>"$log"; then
    echo "FAIL $name (exit status)"; sed 's/^/    /' "$log"; fail=1; return
  fi
  if grep -q '__LOOPSCHEDULE_DATA__' "$out/$name.html"; then
    echo "FAIL $name (data not embedded)"; fail=1; return
  fi
  if ! check_json "$out/$name.json" "$name" 2>>"$log"; then
    echo "FAIL $name (schedule data check)"; sed 's/^/    /' "$log"; fail=1; return
  fi
  echo "ok   $name: $(tail -n 1 "$log" | sed 's/^loopschedule-vis: //')"
}

for f in "$here"/inputs/*.mlir; do
  name=$(basename "$f" .mlir)
  case $name in
    synthetic*)
      run_one "$name" "$f"
      if [ -f "$out/$name.log" ] && ! grep -q 'unrecognized loopschedule op' "$out/$name.log"; then
        echo "FAIL $name (expected an unrecognized-op warning)"; fail=1
      fi ;;
    *) run_one "$name" "$f" --werror ;;
  esac
done

# Query CLI: offline, from IR and from --json output.
syn="$here/inputs/synthetic.ls.mlir"
check_query() {
  local what=$1; shift
  if ! out_q=$("$tool" query "$@" 2>&1) || ! printf '%s' "$out_q" | python3 -c "$PYCHECK" 2>>"$out/query.log"; then
    echo "FAIL query $what"; printf '%s\n' "$out_q" | head -20 | sed 's/^/    /'; fail=1; return
  fi
  echo "ok   query $what"
}
PYCHECK='import json,sys; d=json.load(sys.stdin); assert d["inputs"][0]["from_id"]==0 and d["src_line"]==5, d' \
  check_query "op (IR)" "$syn" op 3
PYCHECK='import json,sys; d=json.load(sys.stdin); assert d["inputs"][0]["from_id"]==0, d' \
  check_query "op (json)" "$out/synthetic.ls.json" op 3
PYCHECK='import json,sys; d=json.load(sys.stdin); assert d["function_args"][0]["c_name"]=="a" and d["memrefs"][0]["label"]=="a", d' \
  check_query "value %arg0" "$syn" value %arg0
PYCHECK='import json,sys; d=json.load(sys.stdin); assert [s["line"] for s in d["source_lines"]]==[1,5], d' \
  check_query "value a" "$syn" value a
PYCHECK='import json,sys; d=json.load(sys.stdin); assert len(d["carried_edges"])==4 and d["mrt"][0]["peak"]==1, d' \
  check_query "pipeline" "$syn" pipeline 0
PYCHECK='import sys; t=sys.stdin.read(); assert "#3 %4 = arith.mulf" in t and "%1#0<-#0 reg+1r" in t, t' \
  check_query "cdfg" "$syn" cdfg 0 --stage 1
if "$tool" query "$syn" op 999 >/dev/null 2>&1; then echo "FAIL query op 999 (expected an error)"; fail=1; fi

# Server: API, selection round trip and the ask bridge with a stub agent that
# echoes a digest of the prompt it receives on stdin.
port_file="$out/serve.port"; rm -f "$port_file"
"$tool" serve "$syn" --port 0 --port-file "$port_file" \
  --agent-cmd "python3 -c 'import sys; p=sys.stdin.read(); print(\"STUB\", \"focused_op\" in p, \"api/help\" in p, len(p))'" \
  2>"$out/serve.log" &
srv=$!
for _ in $(seq 50); do [ -s "$port_file" ] && break; sleep 0.1; done
if [ ! -s "$port_file" ]; then
  echo "FAIL serve (did not start)"; sed 's/^/    /' "$out/serve.log"; fail=1
else
  base="http://127.0.0.1:$(cat "$port_file")"
  if python3 - "$base" <<'EOF' 2>>"$out/serve.log"
import json, sys, urllib.request, urllib.error
base = sys.argv[1]
def get(p):
  return json.load(urllib.request.urlopen(base + p))
def post(p, body, headers=None):
  h = {'Content-Type': 'application/json'}
  h.update(headers or {})
  req = urllib.request.Request(base + p, json.dumps(body).encode(), h)
  return json.load(urllib.request.urlopen(req))
assert get('/api/ping')['agent'], 'no agent'
assert get('/api/op/3')['id'] == 3
assert get('/api/stage?pipeline=0&stage=1')['ops'][0]['id'] == 3
assert get('/api/value?name=%25arg0')['function_args'][0]['c_name'] == 'a'
assert 'text' in get('/api/cdfg/0')
html = urllib.request.urlopen(base + '/').read().decode()
assert 'id="askBtn"' in html and '__LOOPSCHEDULE_DATA__' not in html
sel = {'pinned': {'p': 0, 's': 1}, 'op': 3, 'value': 'a', 'line': 5}
assert post('/api/selection', sel)['ok']
ctx = get('/api/selection')['context']
assert ctx['viewing'].startswith('P0·S1') and ctx['focused_op']['id'] == 3, ctx
assert ctx['selected_variable']['memrefs'][0]['label'] == 'a', ctx
a = post('/api/ask', {'question': 'why?'})
assert a['answer'].startswith('STUB True True'), a
try:
  post('/api/selection', sel, {'Origin': 'http://evil.example'})
  raise AssertionError('cross-origin POST accepted')
except urllib.error.HTTPError as e:
  assert e.code == 403
try:
  get('/api/op/999')
  raise AssertionError('bad op accepted')
except urllib.error.HTTPError as e:
  assert e.code == 400
EOF
  then echo "ok   serve: API, selection, ask (stub agent), origin check"
  else echo "FAIL serve"; sed 's/^/    /' "$out/serve.log"; fail=1
  fi
  if ! "$tool" query --server "$base" selection >/dev/null 2>>"$out/serve.log"; then
    echo "FAIL query --server selection"; fail=1
  else
    echo "ok   query --server selection"
  fi
fi
kill $srv 2>/dev/null; wait $srv 2>/dev/null

if [ "${1:-}" = "--run-hls-est" ]; then
  repo=$(cd "$tool_dir/../.." && pwd)
  kernel="test/hls-est/Estimation/polybench/bicg.mlir"
  if (cd "$repo" && [ -f "$kernel" ]); then
    (cd "$repo" && run_one "bicg.run-hls-est" "$kernel" --run-hls-est --werror) || fail=1
  else
    echo "skip --run-hls-est: $kernel not found"
  fi
fi

if [ $fail -ne 0 ]; then
  echo "smoke test FAILED"; exit 1
fi
echo "smoke test passed (outputs in $out)"
