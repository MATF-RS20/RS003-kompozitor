#ifndef KOMPOZITOR_NOTE_TRACK_HPP
#define KOMPOZITOR_NOTE_TRACK_HPP

#include "track.hpp"

class NoteTrack: public Track {

Q_OBJECT

public:
    NoteTrack(int id, QList<QObject*>  notes)
            : _notes(std::move(notes)), Track(id) {}

    explicit NoteTrack(int id) : Track(id) {}

    [[nodiscard]]
    QList<QObject*> notes() const{
        return _notes;
    }

private:
    QList<QObject* > _notes;
};


#endif //KOMPOZITOR_NOTE_TRACK_HPP