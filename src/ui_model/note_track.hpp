#ifndef KOMPOZITOR_NOTE_TRACK_HPP
#define KOMPOZITOR_NOTE_TRACK_HPP

#include "track.hpp"

class NoteTrack: public Track {

Q_OBJECT

public:
    NoteTrack(int id, QList<QObject*>  notes)
            : Track(id), _notes(std::move(notes)) {}

    [[nodiscard]]
    QList<QObject*> notes() const{
        return _notes;
    }

private:
    QList<QObject* > _notes;
};


#endif //KOMPOZITOR_NOTE_TRACK_HPP