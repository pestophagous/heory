!include($$top_srcdir/compiler_flags.pri) { error() }

QT += core qml quick

TEMPLATE = lib
CONFIG += shared

RESOURCES = libresources.qrc

SOURCES += \
    cli_options.cc \
    fsynth.cc \
    lib.cc \
    logging_tags.cc \
    music_notes.cc \
    notation_strings.cc \
    resource_helper.cc \
    resources.cc

HEADERS += \
    cli_options.h \
    fsynth.h \
    lib.h \
    logging_tags.h \
    music_notes.h \
    notation_strings.h \
    resource_helper.h \
    resources.h

# 'pri' usage based on http://archive.is/https://www.toptal.com/qt/vital-guide-qmake
!include(../libstyles/libstyles.pri) { error() }
!include(../util/util.pri) { error() }
!include(fluidsynth.pri) { error() }

target.path = $$top_exe_dir
INSTALLS += target
