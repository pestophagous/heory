//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#include "resource_helper.h"

#include <QtQml/QQmlContext>

namespace heory
{
namespace
{
    ResourceHelper helper;
} // namespace

/*static*/ void ResourceHelper::ExportContextPropertiesToQml( QQmlEngine* engine )
{
    engine->rootContext()->setContextProperty( "resourceHelper", &helper );
}

} // namespace heory
