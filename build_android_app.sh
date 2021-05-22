#!/bin/bash

#
# Copyright (c) 2020, 219 Design, LLC
# See LICENSE.txt
#
# https://www.219design.com
# Software | Electrical | Mechanical | Product Design
#

set -Eeuxo pipefail # https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR  # enter this script's directory. (in case called from root of repository)

if [ -f fluidsynth/.git ]; then
  echo "Skipping any work in fluidsynth submodule. Looks done already."
else
  git submodule update --init fluidsynth
fi

tools/ci/get_android_toolchain.sh
tools/ci/build_oboe_for_android.sh
tools/ci/build_fluidsynth_for_android.sh
tools/ci/build_android_app.sh build/for_android "CONFIG+=force_debug_info"

echo 'We assume this was run with '\''set -e'\'' (look at upper lines of this script).'
echo 'Assuming so, then getting here means:'
echo 'build_android_app.sh SUCCESS'
