#ifndef KOMPOZITOR_MAIN_MODEL_HPP
#define KOMPOZITOR_MAIN_MODEL_HPP

#include <QObject>

class MainModel : public QObject {

Q_OBJECT

public slots:
    void playSomething();
    void recordSomething();
};

#endif //KOMPOZITOR_MAIN_MODEL_HPP
