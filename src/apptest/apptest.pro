!include($$top_srcdir/compiler_flags.pri) { error() }

QT += core qml quick

# https://stackoverflow.com/questions/17578150/add-cflags-to-qmake-project-without-hard-coding-them-in-the-pro-file
# https://stackoverflow.com/questions/7754218/qmake-how-to-add-and-use-a-variable-into-the-pro-file
DEFINES += $(CPPFLAGS_DEF_QSTYLE)

TEMPLATE = lib
CONFIG += shared

SOURCES += \
    collection.cc

HEADERS += \
    collection.h

# 'pri' usage based on http://archive.is/https://www.toptal.com/qt/vital-guide-qmake
!include(../lib/fluidsynth_linkonly.pri) { error() }
!include(../lib/lib.pri) { error() }
!include(../util/util.pri) { error() }

target.path = $$top_exe_dir
INSTALLS += target
