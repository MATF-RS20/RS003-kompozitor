#ifndef KOMPOZITOR_MAIN_MODEL_HPP
#define KOMPOZITOR_MAIN_MODEL_HPP

#include <QObject>
#include <QtCore/QTimer>
#include "track_note.hpp"

class MainModel : public QObject {

Q_OBJECT
Q_PROPERTY(bool isRecording READ isRecording)

public:
    QTimer* timer = new QTimer(this);

    bool isRecording() {
        return _isRecording;
    }

public slots:
    void playSomething();
    void recordSomething();
    void playNote(float frequency);
    void MyTimerSlot();

    // For testing purposes
    TrackNote* getTrackNote() const;

    void stopNote(float frequency);

    void startRecording();
    void stopRecording();

private:
    bool _isRecording = false;
};

#endif //KOMPOZITOR_MAIN_MODEL_HPP
