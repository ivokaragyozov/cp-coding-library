#!/usr/bin/env python3
import re
import sys
import argparse
import subprocess
from pathlib import Path
from typing import List, Set

LIBRARY_ROOT = Path(__file__).parent

INCLUDE_RE = re.compile(r'#include\s+"([a-z_/-]+\.hpp)"\s*')
SYSTEM_INCLUDE_RE = re.compile(r'#include\s+<[^>]+>\s*')

STRIP_FROM_HEADERS = {
    "#pragma once",
    "#include <bits/stdc++.h>",
    "using namespace std;",
}


class Expander:
    def __init__(self):
        self.included: Set[Path] = set()
        self.system_includes: dict[str, None] = {}  # ordered set via dict

    def _find_header(self, include_path: str) -> Path:
        path = LIBRARY_ROOT / include_path
        if not path.exists():
            print(f"error: cannot find '{include_path}'", file=sys.stderr)
            sys.exit(1)
        return path

    def _expand_header(self, path: Path) -> List[str]:
        if path in self.included:
            return []
        self.included.add(path)

        lines = []
        for line in path.read_text().splitlines():
            if line.strip() in STRIP_FROM_HEADERS:
                continue
            if SYSTEM_INCLUDE_RE.match(line):
                self.system_includes[line.strip()] = None
                continue
            m = INCLUDE_RE.match(line)
            if m:
                lines.extend(self._expand_header(self._find_header(m.group(1))))
            else:
                lines.append(line)
        return lines

    def expand(self, source: str) -> str:
        self.included = set()
        self.system_includes = {}
        body = []
        for line in source.splitlines():
            if SYSTEM_INCLUDE_RE.match(line):
                self.system_includes[line.strip()] = None
                continue
            m = INCLUDE_RE.match(line)
            if m:
                body.extend(self._expand_header(self._find_header(m.group(1))))
            else:
                body.append(line)

        # Strip leading/trailing blank lines from body so the separator is exactly one blank line.
        while body and body[0].strip() == "":
            body.pop(0)
        while body and body[-1].strip() == "":
            body.pop()

        sorted_includes = sorted(self.system_includes)
        return "\n".join(sorted_includes + [""] + body)


def copy_to_clipboard(text: str) -> None:
    try:
        if sys.platform == "darwin":
            subprocess.run(["pbcopy"], input=text.encode(), check=True)
        elif sys.platform == "win32":
            subprocess.run(["clip"], input=text.encode("utf-16"), check=True)
        else:
            for cmd in [
                ["xclip", "-selection", "clipboard"],
                ["xsel", "--clipboard", "--input"],
            ]:
                try:
                    subprocess.run(cmd, input=text.encode(), check=True)
                    return
                except FileNotFoundError:
                    continue
            print(
                "error: no clipboard tool found (install xclip or xsel)",
                file=sys.stderr,
            )
            sys.exit(1)
    except subprocess.CalledProcessError as e:
        print(f"error: clipboard command failed: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Expand coding library #includes inline into a single file."
    )
    parser.add_argument("source", help="Source .cpp file to expand")
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument(
        "-c",
        "--clipboard",
        action="store_true",
        help="Copy expanded result to clipboard",
    )
    group.add_argument(
        "-i",
        "--inplace",
        action="store_true",
        help="Overwrite the source file with expanded result",
    )
    opts = parser.parse_args()

    source_path = Path(opts.source)
    if not source_path.exists():
        print(f"error: file not found: {opts.source}", file=sys.stderr)
        sys.exit(1)

    expander = Expander()
    output = expander.expand(source_path.read_text())

    if opts.clipboard:
        copy_to_clipboard(output)
        print("Copied to clipboard.")
    else:
        source_path.write_text(output)
        print(f"Written to {source_path}.")
