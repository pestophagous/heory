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
    }

    void TestPitchTrain::IncomingLog(
        QtMsgType, const QMessageLogContext& context, const QString& message )
    {
        if( context.category && std::string( context.category ) == "heory.pitchtraining" )
        {
            fprintf( stderr, "so far so good: %s\n", message.toStdString().c_str() );
        }
    }

} // namespace tests
} // namespace heory
