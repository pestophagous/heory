!android {

QT += qml quick quick-private gui-private core-private widgets

CONFIG += no_import_scan
CONFIG += no_launch_target
CONFIG += console

DEFINES *= QT_USE_QSTRINGBUILDER
DEFINES += QML_RUNTIME_TESTING
#qtConfig(qml-debug): DEFINES += QT_QML_DEBUG_NO_WARNING

SOURCES += qmlscene_main.cpp

TEMPLATE = app
#qtSetQmlPath()

#target.path = $$top_exe_dir
#INSTALLS += target

} # !android
