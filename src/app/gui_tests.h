//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_APP_GUI_TESTS_H
#define PROJECT_APP_GUI_TESTS_H

#include <QQmlApplicationEngine>
#include <QTimer>
#include <QtCore/QObject>

#include <memory>

namespace heory
{
class CliOptions;
class QmlMessageInterceptor;
class Random;

namespace tests
{
    class Collection;
} // namespace tests

class GuiTests : public QObject
{
    Q_OBJECT
public:
    explicit GuiTests( const QQmlApplicationEngine& qmlapp, Random* random,
        QmlMessageInterceptor* messageIntercept, const CliOptions* opt );
    ~GuiTests();

    GuiTests( const GuiTests& ) = delete;
    GuiTests& operator=( const GuiTests& ) = delete;

private:
    void Go();
    void Poll();

    const QQmlApplicationEngine* const m_engine;
    const CliOptions* const m_options;
    Random* const m_random;
    QmlMessageInterceptor* const m_messageIntercept;
    std::unique_ptr<tests::Collection> m_tests;
    QTimer m_timer;
};

} // namespace heory

#endif // PROJECT_APP_GUI_TESTS_H
