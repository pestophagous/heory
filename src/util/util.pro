!include($$top_srcdir/compiler_flags.pri) { error() }

QT += core

TEMPLATE = lib
CONFIG += shared

SOURCES += \
    every_so_often.cc \
    qml_message_interceptor.cc \
    random_concrete.cc

HEADERS += \
    every_so_often.h \
    qml_list_property_helper.h \
    qml_message_interceptor.h \
    random.h \
    random_concrete.h \
    version.h

INCLUDEPATH += $${top_srcdir}

target.path = $$top_exe_dir
INSTALLS += target
