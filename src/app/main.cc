//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "view_model_collection.h"

int main( int argc, char* argv[] )
{
    qSetMessagePattern( "[QT-%{type}][thr:%{threadid}]%{if-category}%{category}: "
                        "%{endif}%{file}(%{line}): %{message}" );
    QGuiApplication app( argc, argv );

    // ViewModels must OUTLIVE the qml engine, so create them first:
    heory::ViewModelCollection vms( app );

    // Created after vms, so that we avoid null vm qml warnings upon vm dtors
    QQmlApplicationEngine engine;

    vms.ExportContextPropertiesToQml( &engine );

    engine.addImportPath( "qrc:///" ); // needed for finding qml in our plugins
    engine.load( QUrl( QStringLiteral( "qrc:///qml/main.qml" ) ) );

    return app.exec();
}
