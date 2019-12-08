#include "playback.hpp"
#include <vector>
#include <SFML/Audio.hpp>
#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>

static std::vector<sf::Int16> create_sample(unsigned frequency = 440, double duration = 10, unsigned sample_rate = 44100) {

    std::vector<sf::Int16> samples(duration * sample_rate);

    unsigned samples_per_phase = sample_rate / frequency;

    for (unsigned long i = 0; i < samples.size(); ++i) {
        double rad_value_inside_phase = ((double) i / (double) samples_per_phase) * M_PI * 2;
        samples[i] = pow(2, 15) * sin(rad_value_inside_phase);
    }

    return samples;
}

static sf::SoundBuffer bufferFromFrequencies(const std::vector<float>& freqs, float duration = 0.5) {

    std::vector<sf::Int16> samples;

    for (const auto &freq : freqs) {
        auto tmp_sample = create_sample(freq, duration);
        samples.insert(samples.end(), tmp_sample.begin(), tmp_sample.end());
    }

    sf::SoundBuffer buffer;
    buffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);
    return buffer;
}

void Playback::play() {
    // Start on a separate thread so that the sound resources don't get deallocated before the playback ends.
    std::thread playThread([](){
        sf::SoundBuffer buffer = bufferFromFrequencies({
            E5, Gs5, E5, Gs5, E5, Gs5, E5, Gs5,
            Ds5, Gs5, Ds5, Gs5,
            E5, E5, E5, Ds5, E5, E5, E5
        }, 0.45);

        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.play();

        std::this_thread::sleep_for(std::chrono::seconds((int) ceil(buffer.getSampleCount() / buffer.getSampleRate()) + 1));
    });

    // Detach the thread because there is currently no need for it to be tracked (it just sleeps and then ends)
    playThread.detach();
}


void Playback::record() {
// TODO

//    std::vector<std::string> availableDevices = sf::SoundRecorder::getAvailableDevices();
//
//    std::string inputDevice = availableDevices[0];
//    sf::SoundBufferRecorder recorder;
//
//    recorder.start();
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//    recorder.stop();
//
//    const sf::SoundBuffer& buffer = recorder.getBuffer();
//    sf::Sound sound(buffer);
//    sound.play();
//    std::cout << buffer.getSamples() << std::endl;
//    sound.setVolume(100);
//    std::this_thread::sleep_for(std::chrono::seconds(3));
//
//    buffer.saveToFile("andja_record.ogg");
}