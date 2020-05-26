//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_APP_GUI_TESTS_HELPERS_H
#define PROJECT_APP_GUI_TESTS_HELPERS_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QVariant>
#include <QtQml/QQmlContext>

#include "util-assert.h"

namespace heory
{
namespace tests
{
    template <class ViewModelType>
    ViewModelType* GetViewModel(
        const QQmlApplicationEngine* engine, const QString& viewModelName )
    {
        QVariant vm = engine->rootContext()->contextProperty( viewModelName );
        const QString variantTypeName( vm.typeName() );
        FASSERT( variantTypeName.contains( "QObject*" ),
            "this code operates on contextProperty(s) of object type" );

        QObject* obj = qvariant_cast<QObject*>( vm );
        ViewModelType* viewModel = dynamic_cast<ViewModelType*>( obj );
        if( !viewModel )
        {
            // If the downcast fails, this might be useful info
            fprintf( stderr, "class: %s\n", obj->metaObject()->className() );
        }

        FASSERT( viewModel, "downcast should not fail here" );
        return viewModel;
    }

} // namespace tests
} // namespace heory

#endif // PROJECT_APP_GUI_TESTS_HELPERS_H
