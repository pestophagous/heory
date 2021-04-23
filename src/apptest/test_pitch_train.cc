//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#include "test_pitch_train.h"

#include <QDebug>

#include "src/apptest/helpers.h"
#include "src/apptest/task_queue.h"
#include "src/lib_app/music_notes.h"
#include "src/util/random.h"

namespace heory
{
namespace tests
{
    TestPitchTrain::TestPitchTrain() = default;
    TestPitchTrain::~TestPitchTrain() = default;

    void TestPitchTrain::Go( const QQmlApplicationEngine* qmlapp, Random* random,
        QmlMessageInterceptor* messageIntercept, const CliOptions* options )
    {
        // clang-format off
        m_taskQueue = std::make_unique<TaskQueue>( std::deque<Task>
            {
        // This is the sequence produced with our repeatable seed in random_concrete.cc
        // This sequence is known to occur repeatably on Ubuntu when compiling with g++-7.
        // If other compilers or build contexts give us a different sequence, then
        // we have several options:
        //   Use conditional compilation to hardcode into the test one sequence per build type.
        //   Write a different implementation of our of RandomConcrete class to be 100% stable.
        //   Parse the log messages that print the next expected midi note, and use that parsed
        //      value instead of the hardcodes

                Task::Log("Next expectation: 67"),
                Task::PlayBasic(67),
                Task::Log("Guess matches expectation"),
                Task::Log("Next expectation: 60"),
                Task::PlayBasic(61),
                Task::Log("Incorrect guess"),
                Task::PlayBasic(60),
                Task::Log("Guess matches expectation"),
                Task::Log("Next expectation: 69"),
                Task::PlayBasic(60),
                Task::Log("Incorrect guess"),
                Task::PlayBasic(67),
                Task::Log("Incorrect guess"),
                Task::PlayBasic(69),
                Task::Log("Guess matches expectation"),
                Task::Log("Next expectation: 70"),
                Task::PlayBasic(70),
                Task::Log("Guess matches expectation"),
                Task::Log("Next expectation: 63"),
                Task::PlayBasic(63),
                Task::Log("Guess matches expectation"),
                Task::Log("Next expectation: 61"),
                Task::PlayBasic(61),
                Task::Log("Guess matches expectation"),
            }
            , QStringList{ "heory.pitchtraining" }
            , messageIntercept
            , options );
        // clang-format on

        random->Reset();

        PitchTrainerVM* viewModel
            = GetViewModel<PitchTrainerVM>( qmlapp, "pitchTrainerViewModel" );

        viewModel->testing();
    }

    bool TestPitchTrain::PollForDoneness()
    {
        return m_taskQueue->PollForDoneness();
    }

} // namespace tests
} // namespace heory
