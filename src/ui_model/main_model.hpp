#ifndef KOMPOZITOR_MAIN_MODEL_HPP
#define KOMPOZITOR_MAIN_MODEL_HPP

#include <QObject>
#include <QtCore/QTimer>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio.hpp>
#include "track_note.hpp"
#include "track.hpp"
#include "note_track.hpp"

class MainModel : public QObject {

Q_OBJECT
Q_PROPERTY(bool isRecordingKeyboard READ isRecordingKeyboard NOTIFY isRecordingKeyboardChanged)
Q_PROPERTY(bool isRecordingMicrophone READ isRecordingMicrophone NOTIFY isRecordingMicrophoneChanged)
Q_PROPERTY(bool isDialog READ isDialog NOTIFY dialogStateChanged)
Q_PROPERTY(QList<Track*> tracks READ tracks WRITE set_tracks NOTIFY onTracksChanged)

public:

    bool isRecordingKeyboard() {
        return _isRecordingKeyboard;
    }
    bool isRecordingMicrophone(){
        return _isRecordingMicrophone;
    }
    bool isDialog() {
        return _isDialog;
    }

    [[nodiscard]]
    QList<Track*> tracks() const;

    void set_tracks(QList<Track*>);

public slots:

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
    void playMelody(int melody);

    void playNote(float frequency);

    void stopNote(float frequency);

    void startRecordingKeyboard(int index);

    void stopRecordingKeyboard(int index);

    void startRecordingMicrophone(int index);

    void stopRecordingMicrophone(int index);

    void addMicrophoneTrack();

    void addKeyboardTrack();

    void calculateOctave(int);

    void addRecordNote(float frequency, int note_position);

    void removeRecordNote(float frequency, int note_position);

    void saveKeyboardComposition();

    void saveMicrophoneComposition();

    void playTrack(int index);

    void stopTrack(int index);

    void deleteTrack(int index);

    void playAllTracks();

    void pauseAllTracks();

    void stopAllTracks();
#pragma clang diagnostic pop

signals:
    void isRecordingKeyboardChanged();

    void isRecordingMicrophoneChanged();

    void onTracksChanged();

    void dialogStateChanged();

private:
    bool _isRecordingKeyboard = false;

    bool _isRecordingMicrophone = false;

    bool _isDialog = false;

    QList<Track *> _tracks;
    int current_octave = 4;
    int fixed_octave = 4;
};

#endif //KOMPOZITOR_MAIN_MODEL_HPP
