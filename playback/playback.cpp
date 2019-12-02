#include "playback.hpp"
#include <vector>
#include <SFML/Audio.hpp>
#include <thread>
#include <chrono>
#include <cmath>

static std::vector<sf::Int16> create_sample(unsigned frequency = 440, double duration = 10, unsigned sample_rate = 44100) {

    std::vector<sf::Int16> samples(duration * sample_rate);

    unsigned phase_size = sample_rate / frequency;

    for (unsigned long i = 0; i < samples.size(); ++i) {
        unsigned i_phased = i % phase_size;
        double rad_value_inside_phase = ((double) i_phased / (double) phase_size) * M_PI / 2;
        samples[i] = pow(2, 15) * sin(rad_value_inside_phase);
    }

    return samples;
}

//        double rad_value_inside_phase = ((double) i / phase_size) * M_PI * 2;

void Playback::play() {
    sf::SoundBuffer buffer;
    std::vector<sf::Int16> samples1 = create_sample(123, 0.5);
    std::vector<sf::Int16> samples2 = create_sample(185, 0.5);
    std::vector<sf::Int16> samples3 = create_sample(123, 0.5);
    std::vector<sf::Int16> samples4 = create_sample(146, 0.5);

    std::vector<sf::Int16> samples;
    samples.insert(samples.end(), samples1.begin(), samples1.end());
    samples.insert(samples.end(), samples2.begin(), samples2.end());
    samples.insert(samples.end(), samples3.begin(), samples3.end());
    samples.insert(samples.end(), samples4.begin(), samples4.end());

    buffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    std::this_thread::sleep_for(std::chrono::seconds(4));
}
