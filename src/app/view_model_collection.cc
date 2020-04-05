//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#include "view_model_collection.h"

#include "gui_tests.h"
#include "qml_message_interceptor.h"
#include "src/lib/cli_options.h"
#include "src/lib/logging_tags.h"
#include "src/lib/resource_helper.h"
#include "src/lib/resources.h"



namespace heory
{

ViewModelCollection::ViewModelCollection( const QGuiApplication& app )
    : m_opts( std::make_unique<CliOptions>( app ) ), m_qmlLogger( std::make_unique<QmlMessageInterceptor>() ), m_logging( std::make_unique<LoggingTags>( *m_opts ) )
{
    heory::initLibResources();

    // Do after the 'init..resource' calls, in case any ctor wants rsrcs:
    // m_navigation = std::make_unique<Navigation>();
}

ViewModelCollection::~ViewModelCollection() = default;

void ViewModelCollection::ExportContextPropertiesToQml( QQmlApplicationEngine* engine )
{
    // m_navigation->ExportContextPropertiesToQml( engine );
    m_logging->ExportContextPropertiesToQml( engine );
    ResourceHelper::ExportContextPropertiesToQml( engine );

    // Keep this at the END of the 'ExportContext...' method, so all view models are exported before any tests run
    if( m_opts->RunningGuiTests() )
    {
        m_guiTests = std::make_unique<GuiTests>( *engine );
    }
}


} // namespace heory

