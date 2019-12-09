#include "mytimer.hpp"
#include <QDebug>
#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>

MyTimer::MyTimer(int time) {
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()),
            this, SLOT(MyTimerSlot()));

    timer->setSingleShot(true);
    timer->start(time);
}

void MyTimer::MyTimerSlot (){
    std::cout << "Music finished..." << std::endl;
    auto over = std::move(buffer);
    if (!buffer)
        std::cout << "Memory deallocated!" << std::endl;
}

