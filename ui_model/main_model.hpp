#ifndef KOMPOZITOR_MAIN_MODEL_HPP
#define KOMPOZITOR_MAIN_MODEL_HPP

#include <QObject>
#include <QtCore/QTimer>

class MainModel : public QObject {

Q_OBJECT
//public:
//    static QTimer *timer;
public slots:
    void playSomething();
    void recordSomething();
    void playNote(float frequency, bool loop = false);
    //void MyTimerSlot();
};

#endif //KOMPOZITOR_MAIN_MODEL_HPP
