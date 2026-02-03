#!/usr/bin/env python3
"""
跨平台 clang-format 格式化脚本（支持 Windows / Linux / macOS）。
支持按扩展名、路径包含/排除过滤文件。
"""

from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path


# 默认要格式化的 C/C++ 扩展名
DEFAULT_EXTENSIONS = {".c", ".cpp", ".cc", ".cxx", ".h", ".hpp", ".hh", ".hxx"}

# 默认排除的目录（与 .gitignore 等常见忽略一致）
DEFAULT_EXCLUDE_DIRS = {
    "build",
    "bin",
    "obj",
    "out",
    "cmake-build-debug",
    "cmake-build-release",
    "vcpkg_installed",
    "conan",
    ".git",
    ".idea",
    ".cache",
    ".vscode",
}

# 默认排除的文件（glob，如第三方头文件不宜被格式化）
DEFAULT_EXCLUDE_GLOBS = ["**/stb_image.h"]


def find_clang_format() -> str | None:
    """在 PATH 中查找 clang-format 可执行文件。"""
    return shutil.which("clang-format")


def resolve_clang_format_path(path_input: str) -> Path | None:
    """
    解析用户输入的 clang-format 路径，支持各平台格式。
    - Windows: 支持 C:\\path\\clang-format.exe、C:/path/clang-format、相对路径
    - Unix: 支持 /usr/bin/clang-format、相对路径
    Path 在 Windows 上同时接受 / 与 \\，解析后得到当前平台可用路径。
    """
    if not path_input or not path_input.strip():
        return None
    p = Path(path_input.strip()).expanduser().resolve()
    if not p.is_file():
        return None
    return p


def find_repo_root(start: Path) -> Path:
    """从 start 向上查找包含 .clang-format 的目录作为仓库根。"""
    current = start.resolve()
    for _ in range(20):
        if (current / ".clang-format").exists():
            return current
        parent = current.parent
        if parent == current:
            break
        current = parent
    return start  # 未找到则用当前目录


def should_skip_dir(path: Path, exclude_dirs: set[str]) -> bool:
    """目录名是否在排除列表中。"""
    return path.name in exclude_dirs


def fnmatch_to_regex(pattern: str) -> re.Pattern:
    """简单 glob 转正则（* 与 ** 仅作前缀/后缀匹配）。"""
    parts = pattern.replace("**/", "\0").replace("*", "[^/]*").replace("\0", ".*")
    return re.compile(f"^{parts}$")


def path_matches_globs(path: Path, globs: list[str], base: Path) -> bool:
    """路径（相对 base）是否匹配任一 glob。"""
    try:
        rel = path.relative_to(base)
    except ValueError:
        return False
    # 统一用正斜杠便于匹配
    rel_str = str(rel).replace("\\", "/")
    for g in globs:
        if fnmatch_to_regex(g.strip()).search(rel_str):
            return True
    return False


def collect_files(
    root: Path,
    base: Path,
    extensions: set[str],
    exclude_dirs: set[str],
    include_globs: list[str] | None,
    exclude_globs: list[str] | None,
) -> list[Path]:
    """收集需要格式化的文件。root=遍历起点，base=用于 glob 匹配的仓库根。"""
    files: list[Path] = []
    for dirpath, dirnames, filenames in os.walk(root, topdown=True):
        dirpath = Path(dirpath)
        # 跳过排除目录（同时避免进入子目录）
        dirnames[:] = [d for d in dirnames if not should_skip_dir(dirpath / d, exclude_dirs)]
        for name in filenames:
            if Path(name).suffix not in extensions:
                continue
            fp = dirpath / name
            if include_globs and not path_matches_globs(fp, include_globs, base):
                continue
            if exclude_globs and path_matches_globs(fp, exclude_globs, base):
                continue
            files.append(fp)
    return sorted(files)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="使用 clang-format 格式化仓库中的 C/C++ 代码，支持文件过滤。"
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="只列出将要格式化的文件，不实际执行",
    )
    parser.add_argument(
        "-i",
        "--in-place",
        action="store_true",
        default=True,
        help="原地修改文件（默认开启）",
    )
    parser.add_argument(
        "--no-in-place",
        action="store_false",
        dest="in_place",
        help="不修改文件，仅检查（可与 --dry-run 等价使用）",
    )
    parser.add_argument(
        "--extensions",
        type=str,
        default=",".join(sorted(DEFAULT_EXTENSIONS)),
        help=f"要格式化的文件扩展名，逗号分隔（默认: {','.join(sorted(DEFAULT_EXTENSIONS))}）",
    )
    parser.add_argument(
        "--include",
        type=str,
        metavar="GLOB",
        action="append",
        default=[],
        help="只处理匹配的路径（可多次指定），例如: --include 'src/**/*.cpp'",
    )
    parser.add_argument(
        "--exclude",
        type=str,
        metavar="GLOB",
        action="append",
        default=[],
        help="排除匹配的路径（可多次指定），例如: --exclude '**/stb_*.h'",
    )
    parser.add_argument(
        "--exclude-dirs",
        type=str,
        metavar="DIR",
        action="append",
        default=[],
        help="额外排除的目录名（可多次指定），默认已排除 build/bin/obj 等",
    )
    parser.add_argument(
        "-c",
        "--clang-format",
        type=str,
        metavar="PATH",
        default=None,
        help="clang-format 可执行文件路径（支持各平台路径格式，如 C:/bin/clang-format.exe 或 /usr/bin/clang-format）",
    )
    parser.add_argument(
        "paths",
        nargs="*",
        type=Path,
        default=[Path("../src")],
        help="要扫描的目录或文件（默认: ../src）",
    )
    args = parser.parse_args()

    if args.clang_format:
        resolved = resolve_clang_format_path(args.clang_format)
        if not resolved:
            print(
                f"错误: 指定的 clang-format 路径不存在或不是文件: {args.clang_format}",
                file=sys.stderr,
            )
            return 1
        clang_format = str(resolved)
    else:
        clang_format = find_clang_format()
        if not clang_format:
            print("错误: 未找到 clang-format，请确保已安装并加入 PATH，或使用 --clang-format 指定路径。", file=sys.stderr)
            return 1

    extensions = {"." + ext.strip().lstrip(".") for ext in args.extensions.split(",") if ext.strip()}
    exclude_dirs = DEFAULT_EXCLUDE_DIRS | set(args.exclude_dirs)
    include_globs = args.include if args.include else None
    exclude_globs = [*DEFAULT_EXCLUDE_GLOBS, *args.exclude]

    # 若传入的是文件，则只处理这些文件（仍做扩展名与 exclude 过滤）
    root = Path(".").resolve()
    root = find_repo_root(root)
    all_files: list[Path] = []

    for p in args.paths:
        p = Path(p).resolve()
        if p.is_file():
            if p.suffix in extensions:
                if exclude_globs and path_matches_globs(p, exclude_globs, root):
                    continue
                if include_globs and not path_matches_globs(p, include_globs, root):
                    continue
                all_files.append(p)
        elif p.is_dir():
            all_files.extend(
                collect_files(p, root, extensions, exclude_dirs, include_globs, exclude_globs)
            )
        else:
            print(f"警告: 跳过不存在的路径: {p}", file=sys.stderr)

    all_files = sorted(set(all_files))

    if not all_files:
        print("没有匹配的文件需要格式化。")
        return 0

    if args.dry_run:
        print(f"将格式化以下 {len(all_files)} 个文件（--dry-run）：")
        for f in all_files:
            print(f"  {f}")
        return 0

    cmd = [clang_format, "-i" if args.in_place else "--output-replacements-xml"]
    cmd.extend(str(f) for f in all_files)

    try:
        subprocess.run(cmd, check=True, cwd=root)
    except subprocess.CalledProcessError as e:
        print(f"clang-format 执行失败: {e}", file=sys.stderr)
        return e.returncode

    print(f"已格式化 {len(all_files)} 个文件。")
    return 0


if __name__ == "__main__":
    sys.exit(main())
