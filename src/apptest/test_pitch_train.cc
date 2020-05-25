//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#include "test_pitch_train.h"

#include <QDebug>

#include "src/apptest/helpers.h"
#include "src/lib/music_notes.h"
#include "src/util/qml_message_interceptor.h"
#include "src/util/random.h"

namespace heory
{
namespace tests
{
    /*
      // This is the sequence produced with our repeatable seed in random_concrete.cc
      // This sequence is know to occur repeatably on Ubuntu when compiling with g++-7.
      // If other compilers or build contexts give us a different sequence, then
      // we have several options:
      //   Use conditional compilation to hardcode into the test one sequence per build type.
      //   Write a different implementation of our of RandomConcrete class to be 100% stable.
      //   Parse the log messages that print the next expected midi note, and use that parsed
      //      value instead of the hardcodes

      log: Next expectation: 67
      play: 67
      log: Guess matches expectation
      log: Next expectation: 60
      play: 61
      log: Incorrect guess
      play: 60
      log: Guess matches expectation
      log: Next expectation: 69
      play: 60
      log: Incorrect guess
      play: 67
      log: Incorrect guess
      play: 69
      log: Guess matches expectation
      log: Next expectation: 70
      play: 70
      log: Guess matches expectation
      log: Next expectation: 63
      play: 63
      log: Guess matches expectation
      log: Next expectation: 61
      play: 61
      log: Guess matches expectation
     */
    TestPitchTrain::~TestPitchTrain() = default;

    void TestPitchTrain::Go( const QQmlApplicationEngine* qmlapp, Random* random,
        QmlMessageInterceptor* messageIntercept )
    {
        random->Reset();

        PitchTrainerVM* viewModel
            = GetViewModel<PitchTrainerVM>( qmlapp, "pitchTrainerViewModel" );

        std::shared_ptr<LogTeeFunctor> sink = std::make_shared<LogTeeFunctor>(
            std::bind( &TestPitchTrain::IncomingLog, this, _1, _2, _3 ) );
        messageIntercept->AddMessageSink( sink );

        viewModel->testing();
        viewModel->testing();
        viewModel->testing();
        viewModel->testing();
        viewModel->testing();
        viewModel->testing();
        viewModel->testing();
        viewModel->testing();
    }

    bool TestPitchTrain::PollForDoneness()
    {
        // TODO: finished if deque is empty
        return true;
    }

    void TestPitchTrain::IncomingLog(
        QtMsgType, const QMessageLogContext& context, const QString& message )
    {
        // front of deque should always have a 'log' item (or else be empty)
        if( context.category && std::string( context.category ) == "heory.pitchtraining" )
        {
            fprintf( stderr, "so far so good: %s\n", message.toStdString().c_str() );
            // if front 'log' item matches:
            //    burn through any actions to get to next log item
        }
    }

} // namespace tests
} // namespace heory
