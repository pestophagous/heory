!include($$top_srcdir/compiler_flags.pri) { error() }

QT += core qml

SOURCES += \
    event_filter.cc \
    gui_tests.cc \
    main.cc \
    view_model_collection.cc

HEADERS += \
    event_filter.h \
    gui_tests.h \
    view_model_collection.h

INCLUDEPATH += $${top_srcdir}/build/generated_files # for version.h

# 'pri' usage based on http://archive.is/https://www.toptal.com/qt/vital-guide-qmake
!include(../apptest/apptest.pri) { error() }
!include(../lib_app/fluidsynth_linkonly.pri) { error() }
!include(../lib_app/lib.pri) { error() }
!include(../libstyles/libstyles.pri) { error() }
!include(../minutil/minutil.pri) { error() }
!include(../util/util.pri) { error() }
