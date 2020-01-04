#ifndef KOMPOZITOR_MAIN_MODEL_HPP
#define KOMPOZITOR_MAIN_MODEL_HPP

#include <QObject>
#include <QtCore/QTimer>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio.hpp>
#include "track_note.hpp"
#include "track.hpp"

class MainModel : public QObject {

Q_OBJECT
Q_PROPERTY(bool isRecordingKeyboard READ isRecordingKeyboard NOTIFY isRecordingKeyboardChanged)
Q_PROPERTY(bool isRecordingMicrophone READ isRecordingMicrophone NOTIFY isRecordingMicrophoneChanged)
Q_PROPERTY(QList<Track*> tracks READ tracks WRITE set_tracks NOTIFY onTracksChanged)

public:
    QTimer* timer = new QTimer(this);

    bool isRecordingKeyboard() {
        return _isRecordingKeyboard;
    }
    bool isRecordingMicrophone(){
        return _isRecordingMicrophone;
    }

    [[nodiscard]]
    QList<Track*> tracks() const;

    void set_tracks(QList<Track*>);

public slots:

    void playMelody(int melody);

    void playNote(float frequency);

    void stopNote(float frequency);

    void startRecordingKeyboard();

    void stopRecordingKeyboard();

    void startRecordingMicrophone();

    void stopRecordingMicrophone();

    void addMicrophoneTrack();

    void addKeyboardTrack();

    void octaveChanged(QString);

    void calculateOctave(int);

    void addRecordNote(float frequency);

    void removeRecordNote(float frequency);

signals:
    void isRecordingKeyboardChanged();

    void isRecordingMicrophoneChanged();

    void onTracksChanged();

private:
    bool _isRecordingKeyboard = false;

    bool _isRecordingMicrophone = false;

    // Test data, for now
    QList<Track*> _tracks {
            new Track(1, Track::KEYBOARD, {
                    new TrackNote(2, 0, 2),
                    new TrackNote(5, 3, 4)
            }),
            new Track(2, Track::MICROPHONE, {
                    new TrackNote(3, 0, 2),
                    new TrackNote(5, 2, 5),
                    new TrackNote(2, 4, 6),
                    new TrackNote(7, 7, 10)
            })
    };
    int current_octave = 4;
    int fixed_octave = 4;
};

#endif //KOMPOZITOR_MAIN_MODEL_HPP
