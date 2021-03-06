//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#include "gui_tests.h"

#include <QCoreApplication>
#include <QTimer>

#include <chrono>

#include "src/apptest/collection.h"
#include "src/apptest/note_player.h"
#include "src/lib_app/cli_options.h"
#include "util-assert.h"

namespace heory
{
namespace
{
    // Don't let this discourage us from ever renaming our qml filenames. This
    // isn't for the purpose of enforcing the precise NAME. Rather, this is used
    // only to give confirmation that we understand what the
    // QQmlEngine creates/loads when the app is run.
    constexpr char EXPECTED_FIRST_LOADED_FILE[] = "main.qml";
} // namespace

GuiTests::GuiTests( QQmlEngine& engine, Random* random,
    QmlMessageInterceptor* messageIntercept, const CliOptions* options )
    : m_engine( &engine )
    , m_options( options )
    , m_random( random )
    , m_messageIntercept( messageIntercept )
    , m_notePlayerForQmlscene( std::make_unique<apptesting::NotePlayer>( options ) )
{
    // Intended for use when ViewModelCollection is used by qmlscene_main
    m_notePlayerForQmlscene->ExportContextPropertiesToQml( &engine );

    if( m_options->RunningGuiTests() )
    {
        const QQmlApplicationEngine* appEngine
            = dynamic_cast<const QQmlApplicationEngine*>( &engine );
        FASSERT( appEngine, "not null. downcast must succeed." );

        connect( appEngine, &QQmlApplicationEngine::objectCreated,
            [=]( QObject*, const QUrl& url ) {
                FASSERT( url.fileName() == QString( EXPECTED_FIRST_LOADED_FILE ),
                    "something must have changed in loading behavior of QQmlEngine" );

                // run tests during an upcoming event-loop cycle:
                QTimer::singleShot( 50 /*milliseconds*/, [this]() { Go(); } );
            } );
    }
}

GuiTests::~GuiTests() = default;

void GuiTests::Go()
{
    m_tests = std::make_unique<tests::Collection>(
        m_engine, m_random, m_messageIntercept, m_options );
    m_tests->Start();

    m_timer.setSingleShot( false );
    m_timer.setInterval( std::chrono::milliseconds( 30 ) );

    connect( &m_timer, &QTimer::timeout, [this]() { Poll(); } );
    m_timer.start();
}

void GuiTests::Poll()
{
    const bool done = m_tests->PollForDoneness();

    if( done )
    {
        m_timer.stop();
        // quit during next event-loop cycle
        QTimer::singleShot(
            1 /*milliseconds*/, QCoreApplication::instance(), QCoreApplication::quit );
    }
}
} // namespace heory
