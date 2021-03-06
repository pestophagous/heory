#!/bin/bash

#
# Copyright (c) 2020, 219 Design, LLC
# See LICENSE.txt
#
# https://www.219design.com
# Software | Electrical | Mechanical | Product Design
#

set -Eeuxo pipefail # https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/

# https://web.archive.org/web/20191121235402/https://confluence.atlassian.com/bitbucket/variables-in-pipelines-794502608.html
if [[ -n ${GITHUB_ACTIONS-} || -n ${BITBUCKET_REPO_OWNER-} || -n ${BITBUCKET_REPO_FULL_NAME-} ]];
# The '-' hyphens above test without angering the 'set -u' about unbound variables
then
  echo "Assuming C.I. environment."
  echo "Found at least one of GITHUB_ACTIONS, BITBUCKET_REPO_OWNER, BITBUCKET_REPO_FULL_NAME in env."

  # Try various ways to print OS version info.
  # This lets us keep a record of this in our CI logs,
  # in case the CI docker images change.
  uname -a       || true
  lsb_release -a || true
  gcc --version  || true  # oddly, gcc often prints great OS information
  cat /etc/issue || true

  # What environment variables did the C.I. system set? Print them:
  env

  ./tools/ci/provision.sh
  ./tools/ci/prep-dummy-soundcard.sh

  XDISPLAY=":1"
else
  echo "Assuming we are NOT on bitbucket. Did not find BITBUCKET_REPO_OWNER nor BITBUCKET_REPO_FULL_NAME in env."
  XDISPLAY=""
fi

tools/formatters/enforce_clang_format.sh check_only
tools/formatters/enforce_qml_format.sh check_only

./build_desktop_app.sh
if [[ -n ${MYAPP_TEMPLATE_BUILD_ANDROID-} ]]; then
  ./build_android_app.sh
fi

# run all test binaries that got built in the expected dir:
tools/auto_test/run_cpp_auto_tests.sh

if [[ -n ${XDISPLAY-} ]]; then
  # 'coproc' so that SIGINT will still work (https://unix.stackexchange.com/a/478697/11592)
  coproc Xvfb ${XDISPLAY} -screen 0 1024x768x16
  VIRT_FB_PID=$!
  sleep 4 # time to (probabilistically) ensure that Xvfb has started
fi

# We rely on VirMIDI:
#  sudo modprobe snd-virmidi
#  ls /dev/snd/midi*
#  https://tldp.org/HOWTO/MIDI-HOWTO-10.html
#
# TODO: we need to check if VirMIDI is ready and if 'amidi -phw:1,0' is correct.
# run gui tests which execute the actual app binary:
tools/gui_test/launch_gui_for_display.sh "${XDISPLAY}"

if [[ -n ${MYAPP_TEMPLATE_BUILD_APPIMAGE-} ]]; then
  # this MUST happen last because (on the C.I. server) it destroys folders (intentionally)
  tools/gui_test/test_AppImage.sh "${XDISPLAY}"
fi

if [[ -n ${XDISPLAY-} ]]; then
   kill -SIGINT $VIRT_FB_PID
fi
