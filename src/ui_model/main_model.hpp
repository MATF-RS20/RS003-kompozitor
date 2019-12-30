#ifndef KOMPOZITOR_MAIN_MODEL_HPP
#define KOMPOZITOR_MAIN_MODEL_HPP

#include <QObject>
#include <QtCore/QTimer>
#include "track_note.hpp"
#include "note_track.hpp"
#include "track.hpp"

class MainModel : public QObject {

Q_OBJECT
Q_PROPERTY(bool isRecording READ isRecording NOTIFY isRecordingChanged)
Q_PROPERTY(QList<Track*> tracks READ tracks WRITE set_tracks NOTIFY onTracksChanged)

public:
    QTimer* timer = new QTimer(this);

    bool isRecording() {
        return _isRecording;
    }

    [[nodiscard]]
    QList<Track*> tracks() const;

    void set_tracks(QList<Track*>);

public slots:

    void playMelody1();

    void recordSomething();

    void playNote(float frequency);

    void stopNote(float frequency);

    void startRecording();

    void stopRecording();

    void addMicrophoneTrack();

    void addKeyboardTrack();

    void octaveChanged(QString);

    void calculateOctave(int);
signals:
    void isRecordingChanged();

    void onTracksChanged();

private:
    bool _isRecording = false;

    // Test data, for now
    QList<Track*> _tracks {
            new NoteTrack(1, {
                    new TrackNote(2, 0, 2),
                    new TrackNote(5, 3, 4)
            }),
            new NoteTrack(2, {
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
