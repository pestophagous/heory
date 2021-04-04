#!/bin/bash

set -Eeuxo pipefail # https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/

CUR_GIT_ROOT=$(git rev-parse --show-toplevel)

cd $CUR_GIT_ROOT

export ANDROID_NDK=${CUR_GIT_ROOT}/dl_third_party/android_kits/ndk-bundle


pushd ${CUR_GIT_ROOT}/oboe >& /dev/null
  cmake --version # to print the version to CI logs.
  ./build_all_android.sh
popd >& /dev/null


echo 'We assume this was run with '\''set -e'\'' (look at upper lines of this script).'
echo 'Assuming so, then getting here means:'
echo 'build_oboe_for_android.sh SUCCESS'
