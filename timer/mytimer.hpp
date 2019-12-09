#ifndef KOMPOZITOR_MYTIMER_HPP
#define KOMPOZITOR_MYTIMER_HPP

#include <QTimer>
#include <SFML/Audio/SoundBuffer.hpp>
#include <chrono>
class MyTimer : public QObject
{
Q_OBJECT
public:
    MyTimer(int);
    QTimer *timer;

public slots:
    void MyTimerSlot();
};

#endif //KOMPOZITOR_MYTIMER_HPP
