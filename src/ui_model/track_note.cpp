#include "track_note.hpp"

TrackNote::TrackNote(QObject *parent) : QObject(parent) {}

int TrackNote::pitch() const {
    return _pitch;
}

void TrackNote::setPitch(int pitch) {
    _pitch = pitch;
}

double TrackNote::start() const {
    return _start;
}

void TrackNote::setStart(double start) {
    _start = start;
}

double TrackNote::end() const {
    return _end;
}

void TrackNote::setEnd(double end) {
    _end = end;
}






