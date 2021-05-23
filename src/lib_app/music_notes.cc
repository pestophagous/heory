#include "music_notes.h"

#include <QDebug>
#include <QtQml/QQmlContext>

#include "src/lib_app/fsynth.h"
#include "src/lib_app/pitch_training.h"
#include "util-assert.h"

#define log_func_human_tag "heory.musicnotes"
#define log_func_preprocessor_symbol mscnttrace
#include "src/util/wrap_qt_trace_category.h"

namespace heory
{
WrapQtTraceCategory thisfiletrace; // OFF by default. try QT_LOGGING_RULES="*=true;qt*=false;"

PitchTrainerVM::PitchTrainerVM( SoundIO_Interface* io, Random* random )
    : m_training(
          std::make_unique<PitchTraining>( Pitch::MiddleC(), Pitch::C5(), io, random ) )
{
}

PitchTrainerVM::~PitchTrainerVM() = default;

void PitchTrainerVM::testing()
{
    m_training->SetEnabled( true );
    m_training->Advance();
}

void PitchTrainerVM::setActive( const bool active )
{
    m_training->SetEnabled( active );
}

MusicNotes::MusicNotes( FsynthWrapper* fsynth, Random* random )
    : m_fsynth( fsynth ), m_pitchTrainerVM( fsynth, random )
{
}

MusicNotes::~MusicNotes() = default;

void MusicNotes::ExportContextPropertiesToQml( QQmlEngine* engine )
{
    thisfiletrace.stream() << "ExportContextProp";
    engine->rootContext()->setContextProperty( "musicNotesViewModel", this );
    engine->rootContext()->setContextProperty( "pitchTrainerViewModel", &m_pitchTrainerVM );
}

void MusicNotes::playTestNote()
{
    m_fsynth->PlayNote( Pitch::MiddleC() );
}

} // namespace heory
