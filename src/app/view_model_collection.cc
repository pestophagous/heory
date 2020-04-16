//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#include "view_model_collection.h"

#include <QtQml/QQmlContext>

#include "gui_tests.h"
#include "src/lib/cli_options.h"
#include "src/lib/fsynth.h"
#include "src/lib/logging_tags.h"
#include "src/lib/music_notes.h"
#include "src/lib/resource_helper.h"
#include "src/lib/resources.h"
#include "src/util/qml_message_interceptor.h"
#include "src/util/version.h" // USE THIS SPARINGLY. IT CAN TRIGGER MANY REBUILDS.

namespace heory
{
// clang-format off
ViewModelCollection::ViewModelCollection( const QGuiApplication& app )
    : m_opts( std::make_unique<CliOptions>( app ) ),
      m_qmlLogger( std::make_unique<QmlMessageInterceptor>( !m_opts->MaximumQtLogging() ) ),
      m_logging( std::make_unique<LoggingTags>( *m_opts ) ),
      m_fsynth( std::make_unique<FsynthWrapper>( *m_opts ) )
// clang-format on
{
    heory::initLibResources();

    // Do after the 'init..resource' calls, in case any ctor wants rsrcs:
    m_musicNotes = std::make_unique<MusicNotes>( m_fsynth.get() );
}

ViewModelCollection::~ViewModelCollection() = default;

void ViewModelCollection::ExportContextPropertiesToQml( QQmlApplicationEngine* engine )
{
    engine->rootContext()->setContextProperty( "versionInfoBuildDateString", BUILD_ON_DATE );
    engine->rootContext()->setContextProperty( "versionInfoGitHash", GIT_HASH_WHEN_BUILT );
    fprintf( stderr, "GUI Build Info: %s %s\n", BUILD_ON_DATE, GIT_HASH_WHEN_BUILT );

    m_logging->ExportContextPropertiesToQml( engine );
    ResourceHelper::ExportContextPropertiesToQml( engine );

    m_musicNotes->ExportContextPropertiesToQml( engine );

    // Keep this at the END of the 'ExportContext...' method, so all view models are exported before any tests run
    if( m_opts->RunningGuiTests() )
    {
        m_guiTests = std::make_unique<GuiTests>( *engine );
    }
}

} // namespace heory
