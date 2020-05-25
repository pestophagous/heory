//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_APP_GUI_TESTS_H
#define PROJECT_APP_GUI_TESTS_H

#include <QQmlApplicationEngine>
#include <QtCore/QObject>

namespace heory
{
class QmlMessageInterceptor;
class Random;

class GuiTests : public QObject
{
    Q_OBJECT
public:
    explicit GuiTests( const QQmlApplicationEngine& qmlapp, Random* random,
        QmlMessageInterceptor* messageIntercept );
    ~GuiTests();

    GuiTests( const GuiTests& ) = delete;
    GuiTests& operator=( const GuiTests& ) = delete;

private:
    void Go();

    const QQmlApplicationEngine* const m_engine;
    Random* const m_random;
    QmlMessageInterceptor* const m_messageIntercept;
};

} // namespace heory

#endif // PROJECT_APP_GUI_TESTS_H
