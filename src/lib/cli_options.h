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
    explicit CliOptions( const QCoreApplication& app );
    ~CliOptions();

    CliOptions( const CliOptions& ) = delete;
    CliOptions& operator=( const CliOptions& ) = delete;

    bool RunningGuiTests() const;

private:
    bool m_guiTests = false;
};

} // namespace heory


#endif // PROJECT_APP_CLI_OPTIONS_H
