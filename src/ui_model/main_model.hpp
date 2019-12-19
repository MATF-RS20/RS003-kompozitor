#ifndef KOMPOZITOR_MAIN_MODEL_HPP
#define KOMPOZITOR_MAIN_MODEL_HPP

#include <QObject>
#include <QtCore/QTimer>
#include "track_note.hpp"

class MainModel : public QObject {

Q_OBJECT
Q_PROPERTY(bool isRecording READ isRecording NOTIFY isRecordingChanged)
Q_PROPERTY(QList<QObject*> notes READ trackNotes NOTIFY trackNotesChanged)

public:
    QTimer* timer = new QTimer(this);

    bool isRecording() {
        return _isRecording;
    }

    [[nodiscard]]
    QList<QObject*> trackNotes() const;

    void setTrackNotes(QList<QObject*>);

public slots:
    void playSomething();
    void recordSomething();
    void playNote(float frequency);
    void MyTimerSlot();

    void stopNote(float frequency);

    void startRecording();
    void stopRecording();

signals:
    void isRecordingChanged();

    void trackNotesChanged();

private:
    bool _isRecording = false;

    // Test data, for now
    QList<QObject*> _trackNotes {
            new TrackNote(2, 0, 2),
            new TrackNote(5, 3, 4)
    };
};

#endif //KOMPOZITOR_MAIN_MODEL_HPP
