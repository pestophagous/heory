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
    class TaskQueue;

    class TestPitchTrain : public TestInterface
    {
    public:
        TestPitchTrain();
        ~TestPitchTrain();

        void Go( const QQmlApplicationEngine* qmlapp, Random* random,
            QmlMessageInterceptor* messageIntercept ) override;

        bool PollForDoneness() override;

    private:
        std::unique_ptr<TaskQueue> m_taskQueue;
    };

} // namespace tests
} // namespace heory

#endif // PROJECT_APP_GUI_TEST_PITCH_TRAIN_H
