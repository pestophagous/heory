#!/bin/bash

#
# Copyright (c) 2020, 219 Design, LLC
# See LICENSE.txt
#
# https://www.219design.com
# Software | Electrical | Mechanical | Product Design
#

set -Eeuxo pipefail # https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/

echo "reading single argument (should be either empty or ':1' to choose display)"
export DISPLAY="${1:-"$DISPLAY"}"

CUR_GIT_ROOT=$(git rev-parse --show-toplevel)

cd $CUR_GIT_ROOT
rm -f gui_test.log # in C.I. there should never be a leftover file. but perhaps locally.

# -g flag causes app to close when test is done.
# "run, bt, run" is a workaround for a gdb behavior change between gdb 8 and gdb 9
# for more info, see: https://sourceware.org/bugzilla/show_bug.cgi?id=27125
QT_LOGGING_RULES="*=true;qt*=false;" gdb -n -batch -return-child-result -ex "set args -g -v -p \-phw:2,0" -ex "run" -ex "bt" -ex "run" ${CUR_GIT_ROOT}/build/src/app/app 2>&1 |& tee gui_test.log

tools/gui_test/check_gui_test_log.py gui_test.log
rm -f gui_test.log

echo 'We assume this was run with '\''set -e'\'' (look at upper lines of this script).'
echo 'Assuming so, then getting here means:'
echo 'launch_gui_for_display SUCCESS'
