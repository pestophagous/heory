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
class QmlMessageInterceptor;
class Random;

namespace tests
{
    // It's a bit sloppy to put all the 'using' in this header, but since this
    // is only for 'namespace tests' and it saves us boilerplate in each test,
    // we're allowing it.
    using LogTeeFunctor
        = std::function<void( QtMsgType, const QMessageLogContext&, const QString& )>;

    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;

    class TestInterface
    {
    public:
        virtual ~TestInterface() = default;

        virtual void Go( const QQmlApplicationEngine* qmlapp, Random* random,
            QmlMessageInterceptor* messageIntercept )
            = 0;
    };

} // namespace tests
} // namespace heory

#endif // PROJECT_APP_GUI_TESTS_INTERFACE_H
