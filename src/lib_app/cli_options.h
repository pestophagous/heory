//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_APP_CLI_OPTIONS_H
#define PROJECT_APP_CLI_OPTIONS_H

#include <QCoreApplication>

namespace heory
{
class CliOptions
{
public:
    explicit CliOptions( bool dummyObject, const QCoreApplication& app );
    ~CliOptions();

    CliOptions( const CliOptions& ) = delete;
    CliOptions& operator=( const CliOptions& ) = delete;

    bool RunningGuiTests() const;
    bool MaximumQtLogging() const;
    QString AmidiPortToken() const;

private:
    bool m_guiTests = false;
    bool m_maximumQtLogs = false;
    QString m_amidiPortToken;
};

} // namespace heory

#endif // PROJECT_APP_CLI_OPTIONS_H
