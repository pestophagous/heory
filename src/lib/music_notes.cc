#include "music_notes.h"

#include <QDebug>
#include <QtQml/QQmlContext>

#include "src/lib/fsynth.h"
#include "src/lib/pitch_training.h"
#include "util-assert.h"

namespace heory
{
PitchTrainerVM::PitchTrainerVM( SoundIO_Interface* io )
    : m_training( std::make_unique<PitchTraining>( Pitch::MiddleC(), Pitch::C5(), io ) )
{
}

PitchTrainerVM::~PitchTrainerVM() = default;

void PitchTrainerVM::testing()
{
    // m_training->MakeSound();
    m_training->Advance();
}

MusicNotes::MusicNotes( FsynthWrapper* fsynth )
    : m_fsynth( fsynth ), m_pitchTrainerVM( fsynth )
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
