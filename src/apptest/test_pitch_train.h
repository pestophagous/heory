//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_APP_GUI_TEST_PITCH_TRAIN_H
#define PROJECT_APP_GUI_TEST_PITCH_TRAIN_H

#include <memory>

#include "src/apptest/interface.h"

namespace heory
{
namespace tests
{
    class TestPitchTrain : public TestInterface
    {
    public:
        ~TestPitchTrain() override;

        void Go( const QQmlApplicationEngine* qmlapp, Random* random,
            QmlMessageInterceptor* messageIntercept ) override;

    private:
        void IncomingLog(
            QtMsgType type, const QMessageLogContext& context, const QString& message );
    };

} // namespace tests
} // namespace heory

#endif // PROJECT_APP_GUI_TEST_PITCH_TRAIN_H
