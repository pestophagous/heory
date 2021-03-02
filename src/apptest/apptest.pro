!include($$top_srcdir/compiler_flags.pri) { error() }

QT += core qml quick

# https://stackoverflow.com/questions/17578150/add-cflags-to-qmake-project-without-hard-coding-them-in-the-pro-file
# https://stackoverflow.com/questions/7754218/qmake-how-to-add-and-use-a-variable-into-the-pro-file
DEFINES += $(CPPFLAGS_DEF_QSTYLE)

TEMPLATE = lib
CONFIG += shared

SOURCES += \
    collection.cc \
    task.cc \
    task_queue.cc \
    task_runner.cc \
    test_pitch_train.cc

HEADERS += \
    collection.h \
    task.h \
    task_queue.h \
    task_runner.h \
    test_pitch_train.h

# 'pri' usage based on http://archive.is/https://www.toptal.com/qt/vital-guide-qmake
!include(../lib_app/fluidsynth_linkonly.pri) { error() }
!include(../lib_app/lib.pri) { error() }
!include(../util/util.pri) { error() }

target.path = $$top_exe_dir
INSTALLS += target
