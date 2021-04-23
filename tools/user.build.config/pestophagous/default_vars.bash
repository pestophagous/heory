#!/bin/bash

if [ "${BASH_SOURCE[0]}" -ef "$0" ]
then
    echo "Hey, you should source this script, not execute it!"
    exit 1
fi

export MYAPP_TEMPLATE_SKIP_APPIMAGE=1
export QT_LOGGING_RULES="*=true;qt*=false;"
export PATH="/opt/repositories/KEEP_qt5_dbg_install/bin:$PATH"

#export ANDROID_NDK=/opt/repositories/client/self/heory/gits/heory/dl_third_party/android_kits/ndk-bundle
