#!/bin/bash

set -Eeuxo pipefail # https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/

CUR_GIT_ROOT=$(git rev-parse --show-toplevel)

cd $CUR_GIT_ROOT

if [ -f oboe/.git ]; then
  echo "Skipping any work in oboe submodule. Looks done already."
else
  git submodule update --init oboe
fi

if [ -f prefab/.git ]; then
  echo "Skipping any work in prefab submodule. Looks done already."
else
  git submodule update --init prefab
fi
# get prefab on the PATH
pushd prefab >& /dev/null
  ./gradlew installDist
popd >& /dev/null
export PATH="$PWD/prefab/cli/build/install/prefab/bin/:$PATH"

export ANDROID_NDK=${CUR_GIT_ROOT}/dl_third_party/android_kits/ndk-bundle

pushd ${CUR_GIT_ROOT}/oboe >& /dev/null
  cmake --version # to print the version to CI logs.
  ./prefab_build.sh
popd >& /dev/null


echo 'We assume this was run with '\''set -e'\'' (look at upper lines of this script).'
echo 'Assuming so, then getting here means:'
echo 'build_oboe_for_android.sh SUCCESS'
