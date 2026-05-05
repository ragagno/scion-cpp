#!/usr/bin/env bash

# Builds and installs the CMake project for the specified configuration. Defaults to release.
# With the default install prefix, the files to delete are installed under /usr/local, so you will likely be prompted for permission escalation.
# Since this script is minimal, it is quite strict about its arguments, basically the most recent overrides.

# To uninstall, manually remove the files that were installed by this script.
# The installation path depends on your system's install prefix.
# At the time of writing, the default install prefix is /usr/local.
# So the files to delete are
# - /usr/local/include/scion/*
# - /usr/local/lib/libscion.a
# - /usr/local/lib/cmake/scion/*
# You may also want to remove the directories
# - /usr/local/include/scion
# - /usr/local/lib/cmake/scion

# Alternatively, you can also use this project without installing it through CMake's add_subdirectory().

set -euo pipefail

CONFIG="release"
PREFIX=""

while [[ $# -gt 0 ]]; do
  case "$1" in
    --config) CONFIG="$2"; shift 2 ;;
    --prefix) PREFIX="$2"; shift 2 ;;
    *) echo "Unknown argument: $1" >&2; exit 1 ;;
  esac
done

CONFIG="${CONFIG,,}"

case "$CONFIG" in
  debug|profile|release) ;;
  *) echo "Error: unknown config '${CONFIG}'." >&2; exit 1 ;;
esac

if [[ -n "${PREFIX}" ]]; then
    cmake --install "./build/cmake-build-${CONFIG}" --prefix "${PREFIX}" --config "${CONFIG}"
else
    cmake --install "./build/cmake-build-${CONFIG}" --config "${CONFIG}"
fi
