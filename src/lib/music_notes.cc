#include "music_notes.h"

#include <QDebug>
#include <QtQml/QQmlContext>

#include "src/lib/fsynth.h"
#include "src/lib/pitch_training.h"
#include "util-assert.h"

namespace heory
{
PitchTrainerVM::PitchTrainerVM( SoundIO_Interface* io, Random* random )
    : m_training(
          std::make_unique<PitchTraining>( Pitch::MiddleC(), Pitch::C5(), io, random ) )
{
}

PitchTrainerVM::~PitchTrainerVM() = default;

void PitchTrainerVM::testing()
{
    // m_training->MakeSound();
    m_training->Advance();
}

MusicNotes::MusicNotes( FsynthWrapper* fsynth, Random* random )
    : m_fsynth( fsynth ), m_pitchTrainerVM( fsynth, random )
{
}

MusicNotes::~MusicNotes() = default;

void MusicNotes::ExportContextPropertiesToQml( QQmlEngine* engine )
{
    engine->rootContext()->setContextProperty( "musicNotesViewModel", this );
    engine->rootContext()->setContextProperty( "pitchTrainerViewModel", &m_pitchTrainerVM );
}

void MusicNotes::playTestNote()
{
    m_fsynth->PlayNote( Pitch::MiddleC() );
}

} // namespace heory
