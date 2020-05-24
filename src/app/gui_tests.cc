//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#include "gui_tests.h"

#include <QCoreApplication>
#include <QTimer>

#include "src/apptest/collection.h"
#include "util-assert.h"

namespace heory
{
namespace
{
    // Don't let this discourage us from ever renaming our qml filenames. This
    // isn't for the purpose of enforcing the precise NAME. Rather, this is used
    // only to give confirmation that we understand what the
    // QQmlApplicationEngine creates/loads when the app is run.
    constexpr char EXPECTED_FIRST_LOADED_FILE[] = "main.qml";
} // namespace

GuiTests::GuiTests( const QQmlApplicationEngine& engine, Random* random )
    : m_engine( &engine ), m_random( random )
{
    connect( &engine, &QQmlApplicationEngine::objectCreated, [=]( QObject*, const QUrl& url ) {
        FASSERT( url.fileName() == QString( EXPECTED_FIRST_LOADED_FILE ),
            "something must have changed in loading behavior of QQmlApplicationEngine" );

        // run tests during an upcoming event-loop cycle:
        QTimer::singleShot( 50 /*milliseconds*/, [this]() { Go(); } );
    } );
}

GuiTests::~GuiTests() = default;

void GuiTests::Go()
{
    tests::Collection tests( m_engine, m_random );
    tests.Go();

    // quit during next event-loop cycle
    QTimer::singleShot(
        1 /*milliseconds*/, QCoreApplication::instance(), QCoreApplication::quit );
}

} // namespace heory
