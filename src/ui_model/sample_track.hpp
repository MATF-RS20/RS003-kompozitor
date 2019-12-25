#ifndef KOMPOZITOR_SAMPLE_TRACK_HPP
#define KOMPOZITOR_SAMPLE_TRACK_HPP

#include "track.hpp"

#include <utility>

class SampleTrack: public Track {
Q_OBJECT
public:
    SampleTrack(int id, QList<double> samples)
        : Track(id), _samples(std::move(samples)) {}

    [[nodiscard]]
    QList<double> samples() const {
        return _samples;
    }

private:
    QList<double> _samples;
};


#endif //KOMPOZITOR_SAMPLE_TRACK_HPP