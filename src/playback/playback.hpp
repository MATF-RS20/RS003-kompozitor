#ifndef KOMPOZITOR_PLAYBACK_HPP
#define KOMPOZITOR_PLAYBACK_HPP

#include <memory>
#include <SFML/Audio.hpp>
#include <QtCore/QTimer>
#include <unordered_set>

const float C4 = 261.63;
const float Cs4 = 277.18;
const float D4 = 293.66;
const float Ds4 = 311.13;
const float E4 = 329.63;
const float F4 = 349.23;
const float Fs4 = 369.99;
const float G4 = 392.00;
const float Gs4 = 415.30;
const float A4 = 440.00;
const float As4 = 466.16;
const float B4 = 493.88;
const float C5 = 523.25;

namespace Playback {
    void play(int melody_played);
    //sf::SoundBuffer record();

    std::vector<sf::Int16> buffer_data_from_multiple_notes(const std::unordered_set<double> &notes, unsigned duration = 5, unsigned sample_rate = 44100);
    std::vector<double> create_sample(unsigned frequency = 440, double duration = 10, unsigned sample_rate = 44100);
}

#endif //KOMPOZITOR_PLAYBACK_HPP
