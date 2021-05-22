#!/bin/bash

set -Eeuxo pipefail # https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/

CUR_GIT_ROOT=$(git rev-parse --show-toplevel)

cd $CUR_GIT_ROOT

export ANDROID_NDK=${CUR_GIT_ROOT}/dl_third_party/android_kits/ndk-bundle


pushd ${CUR_GIT_ROOT}/fluidsynth >& /dev/null
  cmake --version # to print the version to CI logs.
  ./build_all_android.sh ${CUR_GIT_ROOT}/build/build_fsynth_for_android
popd >& /dev/null

top_level_abi_dirs=(${CUR_GIT_ROOT}/build/build_fsynth_for_android/*/)

for dir in "${top_level_abi_dirs[@]}"; do
  # See https://github.com/pestophagous/heory/issues/34
  ${CUR_GIT_ROOT}/tools/ci/patch_fluid_headers.sh \
    ${CUR_GIT_ROOT}/fluidsynth/src/midi/fluid_midi.h \
    ${CUR_GIT_ROOT}/patch_fluid_midi.h.patch \
    $dir/include
done

echo 'We assume this was run with '\''set -e'\'' (look at upper lines of this script).'
echo 'Assuming so, then getting here means:'
echo 'build_fluidsynth_for_android.sh SUCCESS'
