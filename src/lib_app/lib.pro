!include($$top_srcdir/compiler_flags.pri) { error() }

QT += core qml quick

TEMPLATE = lib
CONFIG += shared

RESOURCES = libresources.qrc

SOURCES += \
    cli_options.cc \
    deck_of_scales.cc \
    fsynth.cc \
    key_signature_drill.cc \
    logging_tags.cc \
    music_enums.cc \
    music_notes.cc \
    notation_strings.cc \
    pitch.cc \
    pitch_training.cc \
    resources.cc \
    scale.cc

android {
    QT += androidextras

    SOURCES += \
        android/intent_to_email.cc
}

HEADERS += \
    cli_options.h \
    deck_of_scales.h \
    fsynth.h \
    incoming_pitch_listener_interface.h \
    key_signature_drill.h \
    logging_tags.h \
    music_enums.h \
    music_notes.h \
    notation_strings.h \
    pitch.h \
    pitch_training.h \
    resources.h \
    scale.h \
    sound_io_interface.h

# 'pri' usage based on http://archive.is/https://www.toptal.com/qt/vital-guide-qmake
!include(../libstyles/libstyles.pri) { error() }
!include(../util/util.pri) { error() }
!include(fluidsynth.pri) { error() }

TARGET = appimpl

target.path = $$top_exe_dir
INSTALLS += target
