# Scion

Scion is a set of general purpose libraries.
This repository is specifically the C++ library.

## Compiler

This library targets C++23.

## Windows support

Windows is **best-effort**.

The codebase builds with MSVC, but scripts and documentation assume a Unix-like shell.

Windows users are expected to either:
- use WSL2
- use Git Bash
- adapt/fix things themselves

## Compile definitions

- `SCION_NOCOLOR` disables ANSI codes for the logging library
- `SCION_NOLOGS` shorthand for all of the following
  - `SCION_NOLOG_ERROR` disables error logs
  - `SCION_NOLOG_INFO` disables informational logs
  - `SCION_NOLOG_WARN` disables warning logs
  - `SCION_NOLOG_DEBUG` disables debug logs (only enabled in `DEBUG` and `PROFILE` builds)
  - `SCION_NOLOG_TRACE` disables trace logs (only enabled in `DEBUG` builds)
