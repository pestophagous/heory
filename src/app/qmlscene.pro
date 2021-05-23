!android {
!include($$top_srcdir/compiler_flags.pri) { error() }

QT += qml quick quick-private gui-private core-private widgets

CONFIG += no_import_scan
CONFIG += no_launch_target
CONFIG += console

DEFINES *= QT_USE_QSTRINGBUILDER
DEFINES += QML_RUNTIME_TESTING
#qtConfig(qml-debug): DEFINES += QT_QML_DEBUG_NO_WARNING

SOURCES += \
    event_filter.cc \
    qmlscene_main.cpp \
    view_model_collection.cc

HEADERS += \
    event_filter.h \
    view_model_collection.h

INCLUDEPATH += $${top_srcdir}
INCLUDEPATH += $${top_srcdir}/build/generated_files # for version.h
!include($$top_srcdir/src/assert/assert.pri) { error() } # allows all code to include util-assert.h

!include(../apptest/apptest.pri) { error() }
!include(../lib_app/fluidsynth_linkonly.pri) { error() }
!include(../lib_app/lib.pri) { error() }
!include(../libstyles/libstyles.pri) { error() }
!include(../minutil/minutil.pri) { error() }
!include(../util/util.pri) { error() }

QMAKE_CXXFLAGS += "\
  -Wno-error=shadow \
  -Wno-error=conversion \
  -Wno-error=float-equal \
  -Wno-error=old-style-cast \
  "

TEMPLATE = app
#qtSetQmlPath()

#target.path = $$top_exe_dir
#INSTALLS += target

} # !android
