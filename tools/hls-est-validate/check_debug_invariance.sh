#!/usr/bin/env bash
# Prove that --bram-debug / --bram-debug-json do not change any estimate.
#
# Runs every test/hls-est/Estimation/**/*.mlir through the default pipeline twice,
# once plain and once with `--bram-debug --bram-debug-json=<tmp>`, and diffs
# the stdout (the --bram-analysis report, including "Total BRAM: N").  Also
# checks that the JSON's total_bram equals the report's total.
#
#   PASS  stdout identical, exit codes identical, JSON total matches
#   FAIL  any of the above differs
#   ERR   hls-est failed or timed out in both runs (reported, not a mismatch)
#
# Env overrides: HLS_EST, PIPELINE, TIMEOUT (seconds, default 60), TESTS (dir).
set -u

CIRCT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
HLS_EST="${HLS_EST:-$CIRCT/build/clion/bin/hls-est}"
# default: common.py DEFAULT_PIPELINE (MEMOS.md M1 and M5, decisions #1 and #4; W3)
PIPELINE="${PIPELINE:---lower-polygeist-subindex --inline --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis}"
TIMEOUT="${TIMEOUT:-60}"
TESTS="${TESTS:-$CIRCT/test/hls-est/Estimation}"

tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT

echo "hls-est : $HLS_EST"
echo "pipeline: $PIPELINE"
echo "tests   : $TESTS (timeout ${TIMEOUT}s each)"
echo

pass=0; fail=0; err=0; n=0
printf '%-5s %-10s %-10s %s\n' STATUS TOTAL JSON CASE
while IFS= read -r f; do
  n=$((n + 1))
  rel="${f#"$TESTS"/}"
  rm -f "$tmp/x.json"
  timeout "$TIMEOUT" "$HLS_EST" "$f" $PIPELINE \
      > "$tmp/plain.out" 2> "$tmp/plain.err"; rc1=$?
  timeout "$TIMEOUT" "$HLS_EST" "$f" $PIPELINE --bram-debug --bram-debug-json="$tmp/x.json" \
      > "$tmp/dbg.out" 2> "$tmp/dbg.err"; rc2=$?

  total="$(grep -m1 '^Total BRAM:' "$tmp/plain.out" | awk '{print $3}')"
  jtotal="-"
  if [ -s "$tmp/x.json" ]; then
    jtotal="$(python3 -c 'import json,sys; print(json.load(open(sys.argv[1]))["total_bram"])' "$tmp/x.json" 2>/dev/null || echo "?")"
  fi

  status=PASS
  if ! cmp -s "$tmp/plain.out" "$tmp/dbg.out"; then
    status=FAIL
    echo "--- stdout differs for $rel:"
    diff "$tmp/plain.out" "$tmp/dbg.out" | head -20
  elif [ "$rc1" -ne "$rc2" ]; then
    status=FAIL
    echo "--- exit code differs for $rel: plain=$rc1 debug=$rc2"
  elif [ "$rc1" -ne 0 ]; then
    status="ERR"
    [ "$rc1" -eq 124 ] && status="ERR" && total="timeout"
  elif [ -n "$total" ] && [ "$jtotal" != "$total" ]; then
    status=FAIL
    echo "--- JSON total_bram ($jtotal) != report total ($total) for $rel"
  fi

  case "$status" in
    PASS) pass=$((pass + 1));;
    FAIL) fail=$((fail + 1));;
    *)    err=$((err + 1));;
  esac
  printf '%-5s %-10s %-10s %s\n' "$status" "${total:-rc=$rc1}" "$jtotal" "$rel"
done < <(find "$TESTS" -name '*.mlir' | sort)

echo
echo "cases=$n pass=$pass fail=$fail err(tool failed/timeout, outputs still identical)=$err"
[ "$fail" -eq 0 ]
