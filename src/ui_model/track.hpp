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

    bool isRecording() const {
        return _isRecording;
    }

    void setIsRecording(bool isRecording) {
        _isRecording = isRecording;
    }

    bool isPlaying() const {
        return _isPlaying;
    }

    void setIsPlaying(bool isPlaying) {
        _isPlaying = isPlaying;
    }

private:
    int _id;
    bool _isRecording = false;
    bool _isPlaying = false;
};

#endif //KOMPOZITOR_TRACK_HPP