#ifndef KOMPOZITOR_MAIN_MODEL_HPP
#define KOMPOZITOR_MAIN_MODEL_HPP

#include <QObject>
#include <QtCore/QTimer>
#include "track_note.hpp"

class MainModel : public QObject {

Q_OBJECT
public:
    QTimer* timer = new QTimer(this);
public slots:
    void playSomething();
    void recordSomething();
    void playNote(float frequency);
    void MyTimerSlot();

    // For testing purposes
    TrackNote* getTrackNote() const;

    void stopNote(float frequency);
};

#endif //KOMPOZITOR_MAIN_MODEL_HPP
