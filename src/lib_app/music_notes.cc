#include "music_notes.h"

#include <QDebug>
#include <QtQml/QQmlContext>

#include "src/lib_app/fsynth.h"
#include "src/lib_app/key_signature_drill.h"
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

KeySigVM::KeySigVM( SoundIO_Interface* io, Random* random )
    : m_drill( std::make_unique<KeySignatureDrill>(
          io, random, std::bind( &KeySigVM::OnNewGuiState, this, std::placeholders::_1 ) ) )
{
    OnNewGuiState( m_drill->GetCurrentGuiState() );
}

KeySigVM::~KeySigVM() = default;

void KeySigVM::OnNewGuiState( KeySignatureDrillGuiState state )
{
    m_tonalityLabel = state.tonalityLabel;
    m_svgFile = "";
    if( !state.svgFile.isEmpty() )
    {
        m_svgFile = QString( "images/key_sig/" ) + state.svgFile;
    }
    m_progressCueLabel = state.progressCueLabel;
    emit SignalAll();
}

void KeySigVM::cancelCueLabel()
{
    m_progressCueLabel = "";
    emit SignalAll();
}

void KeySigVM::setActive( const bool active )
{
    m_drill->SetEnabled( active );
}

QString KeySigVM::GetTonalityLabel() const
{
    return m_tonalityLabel;
}

QString KeySigVM::GetSvgFile() const
{
    return m_svgFile;
}

QString KeySigVM::GetProgressCueLabel() const
{
    return m_progressCueLabel;
}

MusicNotes::MusicNotes( FsynthWrapper* fsynth, Random* random )
    : m_fsynth( fsynth ), m_pitchTrainerVM( fsynth, random ), m_keySigVM( fsynth, random )
{
}

MusicNotes::~MusicNotes() = default;

void MusicNotes::ExportContextPropertiesToQml( QQmlEngine* engine )
{
    thisfiletrace.stream() << "ExportContextProp";
    engine->rootContext()->setContextProperty( "musicNotesViewModel", this );
    engine->rootContext()->setContextProperty( "pitchTrainerViewModel", &m_pitchTrainerVM );
    engine->rootContext()->setContextProperty( "keySigTrainerViewModel", &m_keySigVM );
}

void MusicNotes::playTestNote()
{
    m_fsynth->PlayNote( Pitch::MiddleC() );
}

} // namespace heory
