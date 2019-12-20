#ifndef KOMPOZITOR_TRACK_HPP
#define KOMPOZITOR_TRACK_HPP

#include <QtCore/QObject>
#include <utility>

class Track: public QObject {

public:

    enum TrackType {
        // Explicitly indexed so that it could be used as int in QML
        MICROPHONE = 0,
        KEYBOARD = 1
    };

    Track(int id, TrackType trackType, QList<QObject*>  notes)
        : _id(id), _trackType(trackType), _notes(std::move(notes)) {}

    [[nodiscard]]
    int id() const {
        return _id;
    }

    [[nodiscard]]
    TrackType trackType() const {
        return _trackType;
    }

    [[nodiscard]]
    QList<QObject*> notes() const{
        return _notes;
    }


Q_OBJECT

private:
    int _id;
    TrackType _trackType;
    QList<QObject* > _notes;
};

#endif //KOMPOZITOR_TRACK_HPP