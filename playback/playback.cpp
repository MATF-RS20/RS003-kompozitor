#include "playback.hpp"
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <timer/mytimer.hpp>
sf::Sound sound;
std::unique_ptr<sf::SoundBuffer> buffer;

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

    sf::SoundBuffer my_buffer;
    my_buffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);
    return my_buffer;
}

void Playback::play() {
    sf::SoundBuffer my_buffer = bufferFromFrequencies({
            E5, Gs5, E5, Gs5, E5, Gs5, E5, Gs5,
            Ds5, Gs5, Ds5, Gs5,
            E5, E5, E5, Ds5, E5, E5, E5
            }, 0.45);

    buffer = std::make_unique<sf::SoundBuffer>(my_buffer);
    sound.setBuffer(*buffer.get());
    sound.play();

    auto miliseconds = 1000*((int) ceil(my_buffer.getSampleCount() / my_buffer.getSampleRate()) + 1);
    static MyTimer time(miliseconds);
}

void Playback::record() {
// TODO

    std::vector<std::string> availableDevices = sf::SoundRecorder::getAvailableDevices();

    std::string inputDevice = availableDevices[0];
    sf::SoundBufferRecorder recorder;
    for (auto i: availableDevices){
        std::cout << i << std::endl;
    }

    recorder.start();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    recorder.stop();

    const sf::SoundBuffer& buffer = recorder.getBuffer();
    sf::Sound sound(buffer);
    sound.play();
    std::cout << buffer.getSamples() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));

    buffer.saveToFile("andja_record.ogg");
}




