#!/bin/bash

set -Eeuxo pipefail # https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
CUR_GIT_ROOT=$(git rev-parse --show-toplevel)

echo "Reading first argument. Header to be copied."
HEADER_TO_COPY=$1
shift 1

echo "Reading second argument. Patch to apply."
PATCH_TO_APPLY=$1
shift 1

echo "Reading third argument. Target (destination) directory."
TARGET_DIR=$1
shift 1


# First, attempt to 'ls' this header so that we DOCUMENT how it does _not_ exist:
ls ${TARGET_DIR}/fluidsynth/fluid_midi.h || true
# Now copy the header over (so that it does exist on the include path of our app):
cp ${HEADER_TO_COPY} ${TARGET_DIR}/fluidsynth/
# Patch the fluid_midi.h to allow my app to see some enum declarations and
# midi-parsing functions, but without making visible some other unneeded things
# (such as "fluidsynth_priv.h" and fluid_player)
# See https://github.com/pestophagous/heory/issues/34
patch ${TARGET_DIR}/fluidsynth/fluid_midi.h ${PATCH_TO_APPLY}
