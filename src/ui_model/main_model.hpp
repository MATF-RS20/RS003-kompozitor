#ifndef KOMPOZITOR_MAIN_MODEL_HPP
#define KOMPOZITOR_MAIN_MODEL_HPP

#include <QObject>
#include <QtCore/QTimer>
#include "track_note.hpp"

class MainModel : public QObject {

Q_OBJECT
Q_PROPERTY(bool isRecording READ isRecording NOTIFY isRecordingChanged)
Q_PROPERTY(QList<QObject*> notes READ getTrackNotes NOTIFY notesChanged)

public:
    QTimer* timer = new QTimer(this);

    bool isRecording() {
        return _isRecording;
    }

    // For testing purposes
    [[nodiscard]]
    QList<QObject*> getTrackNotes() const;

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

    void notesChanged();

private:
    bool _isRecording = false;
};

#endif //KOMPOZITOR_MAIN_MODEL_HPP
