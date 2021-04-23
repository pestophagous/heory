//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_APP_GUI_TESTS_INTERFACE_H
#define PROJECT_APP_GUI_TESTS_INTERFACE_H

#include <QQmlApplicationEngine>

namespace heory
{
class CliOptions;
class QmlMessageInterceptor;
class Random;

namespace tests
{
    class TestInterface
    {
    public:
        virtual ~TestInterface() = default;

        virtual void Go( const QQmlApplicationEngine* qmlapp, Random* random,
            QmlMessageInterceptor* messageIntercept, const CliOptions* options )
            = 0;

        // Acts as a timer tick so that test work can make progress.
        // Return TRUE when all tests are done.
        virtual bool PollForDoneness() = 0;
    };

} // namespace tests
} // namespace heory

#endif // PROJECT_APP_GUI_TESTS_INTERFACE_H
