#include "playback.hpp"
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <unordered_set>
#include<climits>

sf::Sound sound; // FIXME avoid global variables
std::unique_ptr<sf::SoundBuffer> buffer;

// Empirically chosen
const double ENDING_INTERVAL = 44100 * 0.005;

static std::vector<double> create_sample(unsigned frequency = 440, double duration = 10, unsigned sample_rate = 44100) {

    static double last_value;

    std::vector<double> samples(duration * sample_rate);

    unsigned samples_per_phase = sample_rate / frequency;

    for (unsigned long i = 0; i < samples.size(); ++i) {
        unsigned long i_phased = i % samples_per_phase;
        double rad_value_inside_phase = last_value + ((double) i_phased / (double) samples_per_phase) * M_PI * 2;
        samples[i] = sin(rad_value_inside_phase);
    }

    // This is equal to the value of the rad_value_inside_phase of the last iteration
    last_value = last_value + ((double) ((samples.size() - 1) % samples_per_phase) / (double) samples_per_phase) * M_PI * 2;

    return samples;
}

std::vector<sf::Int16> Playback::buffer_data_from_multiple_notes(const std::unordered_set<double> &notes, unsigned int duration, unsigned int sample_rate) {
    unsigned buffer_size = duration * sample_rate;
    std::vector<double> raw_buffer_data(buffer_size);
    double max_amplitude = 0;
    for (const auto &note : notes) {
        auto samples = create_sample(note, duration, sample_rate);
        for (unsigned i = 0; i < buffer_size; i++) {
            raw_buffer_data[i] += samples[i];
            if (abs(raw_buffer_data[i]) > max_amplitude) {
                max_amplitude = abs(raw_buffer_data[i]);
            }
        }
    }

    // This is the ratio at which all samples can be amplified, but still avoid clipping
    double amplification_ratio = SHRT_MAX / max_amplitude;

    std::vector<sf::Int16> buffer_data(raw_buffer_data.size());

    for (unsigned i = 0; i < buffer_size; ++i) {
        buffer_data[i] = static_cast<sf::Int16>(raw_buffer_data[i] * amplification_ratio);
    }

    return buffer_data;
}

static sf::SoundBuffer bufferFromFrequencies(const std::vector<float>& freqs, float duration = 0.5) {

    std::vector<sf::Int16> samples;

    for (const auto &freq : freqs) {
//        auto tmp_sample = create_sample(freq, duration);
//        samples.insert(samples.end(), tmp_sample.begin(), tmp_sample.end());
    }

    // Lower the volume of the ending interval to avoid glitching sounds
    for (auto i = (unsigned long) (samples.size() - ENDING_INTERVAL); i < samples.size(); i++) {
        samples[i] = static_cast<float>(samples[i]) * static_cast<float>((samples.size() - i)) / ENDING_INTERVAL;
    }

    sf::SoundBuffer my_buffer;
    my_buffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);
    return my_buffer;
}

void Playback::play(QTimer *timer) {
    sf::SoundBuffer my_buffer = bufferFromFrequencies({
            E5, Gs5, E5, Gs5, E5, Gs5, E5, Gs5,
            Ds5, Gs5, Ds5, Gs5,
            E5, E5, E5, Ds5, E5, E5, E5
            }, 0.45);

    buffer = std::make_unique<sf::SoundBuffer>(my_buffer);
    sound.setBuffer(*buffer);
    sound.play();

    auto milliseconds = 1000*((int) ceil(static_cast<double>(my_buffer.getSampleCount()) / my_buffer.getSampleRate()) + 1);
    make_timer(timer, milliseconds);
}

void Playback::record() {
    // TODO this function needs improving and removal of the debug output
    std::vector<std::string> availableDevices = sf::SoundRecorder::getAvailableDevices();

    std::string inputDevice = availableDevices[0];
    sf::SoundBufferRecorder recorder;
    for (const auto& device: availableDevices){
        std::cout << device << std::endl;
    }

    recorder.start();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    recorder.stop();

    const sf::SoundBuffer& buffer = recorder.getBuffer(); // FIXME remove global variable `buffer`
    sf::Sound sound(buffer); // FIXME remove global variable `sound`
    sound.play();
    std::cout << buffer.getSamples() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));

    buffer.saveToFile("andja_record.ogg");
}

void Playback::make_timer(QTimer* timer, int time) {
    QObject::connect(timer, SIGNAL(timeout()),
                     timer->parent(), SLOT(MyTimerSlot()));
    timer->setSingleShot(true);
    timer->start(time);
}

void Playback::my_timer_slot() {
    std::cout << "Music finished..." << std::endl;
    auto over = std::move(buffer);
    if (!buffer)
        std::cout << "Memory deallocated!" << std::endl;
}





