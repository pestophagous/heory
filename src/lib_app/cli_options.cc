//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#include "cli_options.h"

#include <QCommandLineParser>

namespace heory
{
constexpr char GUI_TEST_CLI_OPT[] = "guitest";
constexpr char MAX_QT_LOGGING_CLI_OPT[] = "maxlogs";
constexpr char GUI_TEST_AMIDI_PORT_OPTSTRING[] = "argforamidi";

CliOptions::CliOptions( bool dummyObject, const QCoreApplication& app )
{
    if( dummyObject )
    {
        return;
    }

    QCommandLineParser parser;
    parser.addHelpOption();

    // clang-format off
    const QCommandLineOption argForAmidi(
        QStringList( {"p", GUI_TEST_AMIDI_PORT_OPTSTRING} ),
        "pass <porttoken> when calling amidi.", "porttoken" );

    parser.addOptions( {
        {{"g", GUI_TEST_CLI_OPT},
               "run automated gui tests (app will SHUT DOWN soon after launch)"},
        {{"v", MAX_QT_LOGGING_CLI_OPT},
               "verbose/maximum logging. uses Qt stderr log even when also "
               "tee-ing to backend file log"},
        argForAmidi} );
    // clang-format on

    parser.process( app );

    m_guiTests = parser.isSet( GUI_TEST_CLI_OPT );
    m_maximumQtLogs = parser.isSet( MAX_QT_LOGGING_CLI_OPT );
    if( parser.isSet( GUI_TEST_AMIDI_PORT_OPTSTRING ) )
    {
        m_amidiPortToken = parser.value( argForAmidi );
    }
}

CliOptions::~CliOptions() = default;

bool CliOptions::RunningGuiTests() const
{
    return m_guiTests;
}

bool CliOptions::MaximumQtLogging() const
{
    return m_maximumQtLogs;
}

QString CliOptions::AmidiPortToken() const
{
    return m_amidiPortToken;
}

} // namespace heory
