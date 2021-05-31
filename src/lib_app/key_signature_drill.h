//
// Copyright (c) 2021, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_KEY_SIGNATURE_DRILL_H
#define PROJECT_LIB_KEY_SIGNATURE_DRILL_H

#include <QString>

#include <functional>

#include "src/lib_app/incoming_pitch_listener_interface.h"
#include "src/lib_app/pitch.h"
#include "src/lib_app/scale.h"
#include "src/lib_app/sound_io_interface.h"

namespace heory
{
class Random;

// It would be nice to make this a nested class, but then it cannot be forward declared.
struct KeySignatureDrillGuiState
{
    QString tonalityLabel;
    QString svgFile;
    QString progressCueLabel;
};

class KeySignatureDrill : public IncomingPitchListener_Interface
{
public:
    explicit KeySignatureDrill( SoundIO_Interface* io, Random* random,
        std::function<void( KeySignatureDrillGuiState )> callback );
    ~KeySignatureDrill() override;

    KeySignatureDrill( const KeySignatureDrill& ) = delete;
    KeySignatureDrill& operator=( const KeySignatureDrill& ) = delete;

    KeySignatureDrillGuiState GetCurrentGuiState() const;

    void Advance();

    void OnIncomingNote( PitchLifetime pitch ) override;

    void SetEnabled( bool enabled );

private:
    SoundIO_Interface* const m_io;
    Random* const m_random;
    std::function<void( KeySignatureDrillGuiState )> m_callback;

    bool m_enabled = false;

    Scale m_currentScale;
    int m_nextScaleIndexAwaiting = 0;
    mutable QString m_pendingProgressIcon;
};

} // namespace heory

#endif // PROJECT_LIB_KEY_SIGNATURE_DRILL_H
