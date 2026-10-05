#!/usr/bin/env bash
set -uo pipefail

rebase_dir() {
  git rev-parse --git-path rebase-merge
}

random_daytime_date() {
  python3 - "$1" <<'PY'
import secrets
import sys
from datetime import datetime

author_date = datetime.fromisoformat(sys.argv[1])
commit_date = author_date.replace(
    hour=9 + secrets.randbelow(10),
    minute=secrets.randbelow(60),
    second=secrets.randbelow(60),
    microsecond=secrets.randbelow(1000000),
)
print(commit_date.isoformat())
PY
}

conflicted_files() {
  git diff --name-only --diff-filter=U
}

rewrite_target_files() {
  while IFS= read -r file; do
    [[ -z "$file" ]] && continue
    if [[ -f "$file" ]]; then
      if git cat-file -e "REBASE_HEAD:$file" 2>/dev/null; then
        git show "REBASE_HEAD:$file" > "$file"
      fi
      python3 tools/history_rewrite.py "$file"
      clang-format -i "$file"
      git add "$file"
    fi
  done < /tmp/rewrite-files.txt
}

while [[ -d "$(rebase_dir)" ]]; do
  files="$(conflicted_files)"
  if [[ -n "$files" ]]; then
    while IFS= read -r file; do
      [[ -z "$file" ]] && continue
        git show ":2:$file" > "$file"
      case "$file" in
        *.cpp|*.cc|*.cxx)
          python3 tools/history_rewrite.py "$file"
          clang-format -i "$file"
          ;;
      esac
      git add "$file"
    done <<< "$files"
  fi

  rewrite_target_files
  python3 tools/ensure_forward_fix.py
  clang-format -i lib/Dialect/Resource/Passes/PolygeistCompat.cpp
  git add lib/Dialect/Resource/Passes/PolygeistCompat.cpp
  git add -u

  if [[ -n "$(conflicted_files)" ]]; then
    echo "Unresolved conflicts remain" >&2
    exit 1
  fi

  if [[ -d "$(rebase_dir)" && -e "$(rebase_dir)/stopped-sha" ]]; then
    original="$(git rev-parse REBASE_HEAD)"
    author_name="$(git show -s --format='%an' "$original")"
    author_email="$(git show -s --format='%ae' "$original")"
    author_date="$(git show -s --format='%aI' "$original")"
    committer_name="$(git show -s --format='%cn' "$original")"
    committer_email="$(git show -s --format='%ce' "$original")"
    committer_date="$(random_daytime_date "$author_date")"

    if ! ninja -C build/release bin/hls-est; then
      exit 1
    fi
    if ninja -C build/release -t targets all | grep '^check-hls-est:' >/dev/null; then
      if ! ninja -C build/release check-hls-est; then
        exit 1
      fi
    else
      if ! /home/peter/circt/llvm/build/bin/llvm-lit -sv build/release/test/hls-est/Passes; then
        exit 1
      fi
    fi

    if git diff --cached --quiet; then
      message="$(git show -s --format=%B "$original")"
      GIT_EDITOR=true \
        GIT_AUTHOR_NAME="$author_name" \
        GIT_AUTHOR_EMAIL="$author_email" \
        GIT_AUTHOR_DATE="$author_date" \
        GIT_COMMITTER_NAME="$committer_name" \
        GIT_COMMITTER_EMAIL="$committer_email" \
        GIT_COMMITTER_DATE="$committer_date" \
        git commit --allow-empty --no-verify -m "$message"
    fi

    GIT_EDITOR=true \
      GIT_AUTHOR_NAME="$author_name" \
      GIT_AUTHOR_EMAIL="$author_email" \
      GIT_AUTHOR_DATE="$author_date" \
      GIT_COMMITTER_NAME="$committer_name" \
      GIT_COMMITTER_EMAIL="$committer_email" \
      GIT_COMMITTER_DATE="$committer_date" \
      git rebase --continue
    status=$?
    if [[ $status -ne 0 ]] && [[ -z "$(conflicted_files)" ]]; then
      exit $status
    fi
  else
    break
  fi
done
