#!/usr/bin/env bash
# Batch BRAM estimation. Conditionally applies --auto-pipeline-unroll only
# where the historical shim prediction in bram-tracking.csv significantly
# undercounts ground-truth BRAM (--infer-vitis-split-array was part of this
# "aggr" mode until it left the default pipeline, MEMOS.md M1).
#   trigger: estimate < 0.75*truth  AND  (truth-estimate) >= 4
#   decision estimate: historical 'BRAM (prediction, shim)' column when numeric,
#                      else a fresh baseline run (pipeline without the two passes).
set -u

BIN="$HOME/circt/bin/hls-est"
ROOT="$HOME/circt/test/hls-est/Estimation"
TRACK="$ROOT/bram-tracking.csv"
LOGDIR="$ROOT/logs"
CSV="$ROOT/results.csv"
TIMEOUT=1000

mkdir -p "$LOGDIR"

# ---- build ground-truth / historical-prediction lookup from bram-tracking.csv ----
lookup="$(mktemp)"
python3 - "$TRACK" > "$lookup" <<'PY'
import csv, sys
with open(sys.argv[1], newline='') as f:
    r = csv.reader(f)
    next(r, None)
    for row in r:
        if len(row) < 3: continue
        ds, bm, tr = row[0].strip(), row[1].strip(), row[2].strip()
        pr = row[10].strip() if len(row) > 10 else ""
        if not ds or not bm: continue
        print(f"{ds}\t{bm}\t{tr}\t{pr}")
PY

declare -A TRUTH PRED
while IFS=$'\t' read -r ds bm tr pr; do
  TRUTH["$ds|$bm"]="$tr"; PRED["$ds|$bm"]="$pr"
done < "$lookup"
rm -f "$lookup"

# ---- helpers ----
csv() {
  local s="$1"
  if [[ "$s" == *,* || "$s" == *\"* || "$s" == *$'\n'* || "$s" == *$'\r'* ]]; then
    s="${s//\"/\"\"}"; printf '"%s"' "$s"
  else printf '%s' "$s"; fi
}
parse_total()  { cat "$1" "$2" 2>/dev/null | grep -oE 'Total BRAM:[[:space:]]*[0-9]+' | head -1 | grep -oE '[0-9]+'; }
parse_nmem()   { cat "$1" "$2" 2>/dev/null | grep -cE '^[[:space:]]*kind='; }
parse_kinds()  { cat "$1" "$2" 2>/dev/null | grep -oE 'kind=[A-Za-z0-9_]+' | sed 's/kind=//' | LC_ALL=C sort -u | paste -sd';' -; }

# run_pipeline MODE FILE TOP OUT ERR  (MODE = base | aggr)
run_pipeline() {
  local mode="$1" f="$2" top="$3" oo="$4" ee="$5" extra=""
  [[ "$mode" == "aggr" ]] && extra="--auto-pipeline-unroll"
  timeout "$TIMEOUT" "$BIN" "$f" \
    --affine-loop-normalize $extra --memory-banking-bram \
    --convert-affine-to-loopschedule \
    --symbol-privatize=exclude="$top" --symbol-dce --bram-analysis >"$oo" 2>"$ee"
  return $?
}

tmp_body="$(mktemp)"
mapfile -t FILES < <(find "$ROOT" -name '*.mlir' -type f | LC_ALL=C sort)

for f in "${FILES[@]}"; do
  rel="${f#$ROOT/}"
  dir="$(dirname "$rel")"; [[ "$dir" == "." ]] && dir=""
  bm="$(basename "$rel" .mlir)"
  if [[ -z "$dir" ]]; then ds=""
  elif [[ "$dir" == *_xilinx ]]; then ds="$dir"
  else ds="${dir}_xilinx"; fi
  key="$ds|$bm"
  truth="${TRUTH[$key]:-}"
  hist="${PRED[$key]:-}"
  log="$LOGDIR/$(echo "$rel" | sed 's#/#__#g').log"

  # --- top function ---
  top="$(grep -E 'func\.func @[A-Za-z0-9_$.]+.*hls\.allocation' "$f" \
          | grep -oE 'func\.func @[A-Za-z0-9_$.]+' | head -1 | sed 's/func\.func @//')"
  rule=""
  if [[ -n "$top" ]]; then rule="hls.allocation"
  else
    mapfile -t funcs < <(grep -oE 'func\.func @[A-Za-z0-9_$.]+' "$f" | sed 's/func\.func @//')
    for fn in "${funcs[@]}"; do
      if [[ "$fn" =~ ^_Z[0-9]+top || "$fn" =~ ^_Z[0-9]+kernel || "$fn" == "top" || "$fn" == "kernel" ]]; then
        top="$fn"; rule="name"; break; fi
    done
    if [[ -z "$top" ]]; then
      if [[ "${#funcs[@]}" -eq 1 ]]; then top="${funcs[0]}"; rule="single"
      elif [[ "${#funcs[@]}" -ge 1 ]]; then top="${funcs[-1]}"; rule="last"; fi
    fi
  fi

  # --- decide whether to apply the two passes ---
  est=""; source="none"; apply="no"
  ran_base=0; b_oo="$(mktemp)"; b_ee="$(mktemp)"; b_code=""; b_elapsed=""
  if [[ -n "$truth" ]]; then
    if [[ "$hist" =~ ^[0-9]+$ ]]; then
      est="$hist"; source="hist"
    else
      s="$(date +%s.%N)"; run_pipeline base "$f" "$top" "$b_oo" "$b_ee"; b_code=$?
      e="$(date +%s.%N)"; b_elapsed="$(awk "BEGIN{printf \"%.1f\", $e-$s}")"
      ran_base=1; est="$(parse_total "$b_oo" "$b_ee")"; source="baseline"
    fi
    if [[ "$est" =~ ^[0-9]+$ ]] && awk "BEGIN{exit !($est < 0.75*$truth && $truth-$est >= 4)}"; then
      apply="yes"
    fi
  fi

  # --- final run ---
  f_oo="$(mktemp)"; f_ee="$(mktemp)"
  if [[ "$apply" == "yes" ]]; then
    mode="aggr"
    s="$(date +%s.%N)"; run_pipeline aggr "$f" "$top" "$f_oo" "$f_ee"; code=$?
    e="$(date +%s.%N)"; elapsed="$(awk "BEGIN{printf \"%.1f\", $e-$s}")"
  elif [[ $ran_base -eq 1 ]]; then
    mode="base(reused)"; cp "$b_oo" "$f_oo"; cp "$b_ee" "$f_ee"; code=$b_code; elapsed="$b_elapsed"
  else
    mode="base"
    s="$(date +%s.%N)"; run_pipeline base "$f" "$top" "$f_oo" "$f_ee"; code=$?
    e="$(date +%s.%N)"; elapsed="$(awk "BEGIN{printf \"%.1f\", $e-$s}")"
  fi

  total_bram="$(parse_total "$f_oo" "$f_ee")"
  num_memrefs="$(parse_nmem "$f_oo" "$f_ee")"
  ram_kinds="$(parse_kinds "$f_oo" "$f_ee")"
  error="$(grep -E 'error:' "$f_ee" | head -1 || true)"

  if   [[ $code -eq 124 ]]; then status="TIMEOUT"
  elif [[ $code -ne 0 ]];   then status="FAIL"
  elif [[ -n "$total_bram" ]]; then status="OK"
  else status="NO_TOTAL"; fi

  { echo "### $rel  top=$top rule=$rule";
    echo "### truth=$truth hist_pred=$hist decision_estimate=$est source=$source passes_applied=$apply mode=$mode";
    echo "### exit=$code elapsed=${elapsed}s status=$status";
    echo "----- stderr -----"; cat "$f_ee";
    echo "----- stdout -----"; cat "$f_oo"; } > "$log"

  {
    csv "$rel"; printf ','; csv "$ds"; printf ','; csv "$bm"; printf ','
    csv "$top"; printf ','; csv "$rule"; printf ','
    csv "$truth"; printf ','; csv "$hist"; printf ','; csv "$est"; printf ','; csv "$source"; printf ','
    csv "$apply"; printf ','; csv "$status"; printf ','; csv "$code"; printf ','
    csv "$total_bram"; printf ','; csv "$num_memrefs"; printf ','; csv "$ram_kinds"; printf ','
    csv "$elapsed"; printf ','; csv "$error"; printf ','; csv "$log"; printf '\n'
  } >> "$tmp_body"

  printf '%-42s truth=%-6s est=%-5s(%-8s) apply=%-3s %-8s bram=%-6s %ss\n' \
    "$rel" "${truth:-NA}" "${est:-NA}" "$source" "$apply" "$status" "${total_bram:-NA}" "$elapsed"

  rm -f "$b_oo" "$b_ee" "$f_oo" "$f_ee"
done

{
  echo 'test,dataset,benchmark,top_func,top_rule,truth_bram,hist_pred,decision_estimate,decision_source,passes_applied,status,exit_code,total_bram,num_memrefs,ram_kinds,elapsed_s,error,log'
  cat "$tmp_body"
} > "$CSV"
rm -f "$tmp_body"

echo
echo "==================== SUMMARY ===================="
total=${#FILES[@]}
echo "tests: $total"
echo "passes applied: $(awk -F, 'NR>1 && $10=="yes"' "$CSV" | wc -l)   not applied: $(awk -F, 'NR>1 && $10!="yes"' "$CSV" | wc -l)"
for st in OK NO_TOTAL FAIL TIMEOUT; do
  n=$(awk -F, 'NR>1{print $11}' "$CSV" | grep -Fxc "$st" || true)
  echo "  $st: $n"
done
echo
echo "Non-OK tests:"
awk -F, 'NR>1 && $11!="OK"{printf "  [%s] %s  %s\n",$11,$1,$17}' "$CSV"
echo "CSV: $CSV"
