#ifndef KOMPOZITOR_TRACK_HPP
#define KOMPOZITOR_TRACK_HPP

#include <QtCore/QObject>

class Track: public QObject {
Q_OBJECT
public:
    explicit Track(int id) : _id(id) {}

    [[nodiscard]]
    int id() const {
        return _id;
    }

private:
    int _id;
};

#endif //KOMPOZITOR_TRACK_HPP