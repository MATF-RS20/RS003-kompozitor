#ifndef KOMPOZITOR_TRACK_NOTE_HPP
#define KOMPOZITOR_TRACK_NOTE_HPP

#include <QObject>

class TrackNote : public QObject {
    Q_OBJECT
    Q_PROPERTY(int pitch READ pitch WRITE setPitch)
    Q_PROPERTY(double start READ start WRITE setStart)
    Q_PROPERTY(double end READ end WRITE setEnd)

public:
    explicit TrackNote(QObject *parent = nullptr);

    TrackNote(int pitch, double start, double end)
        : _pitch(pitch), _start(start), _end(end) {};

    [[nodiscard]]
    int pitch() const;
    void setPitch(int pitch);

    [[nodiscard]]
    double start() const;
    void setStart(double start);

    [[nodiscard]]
    double end() const;
    void setEnd(double end);

private:
    int _pitch;
    double _start;
    double _end;
};


#endif //KOMPOZITOR_TRACK_NOTE_HPP
