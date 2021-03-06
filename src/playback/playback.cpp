#include "playback.hpp"
#include "sound_manager.hpp"
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>
#include <unordered_set>
#include <climits>
#include <QtDebug>

// Empirically chosen
const double ENDING_INTERVAL = 44100 * 0.005;

std::vector<double> Playback::create_sample(unsigned frequency, double duration, unsigned sample_rate) {

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
       auto tmp_sample = Playback::create_sample(freq, duration);
       samples.insert(samples.end(), tmp_sample.begin(), tmp_sample.end());
    }

    // Lower the volume of the ending interval to avoid glitching sounds
    for (auto i = (unsigned long) (samples.size() - ENDING_INTERVAL); i < samples.size(); i++) {
        samples[i] = static_cast<float>(samples[i]) * static_cast<float>((samples.size() - i)) / ENDING_INTERVAL;
    }

    sf::SoundBuffer my_buffer;
    my_buffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);
    return my_buffer;
}

void Playback::play(int melody) {
    if (melody == -1)
        return;
    std::vector<float> frequencies1 {
            E4, Gs4, E4, Gs4, E4, Gs4, E4, Gs4,
            Ds4, Gs4, Ds4, Gs4,
            E4, E4, E4, Ds4, E4, E4, E4
    };
    std::vector<float> frequencies2 {
            E4, D4, C4, D4, E4, E4, E4, E4, D4, D4,
            D4, E4, G4, G4,
            E4, D4, C4, D4, E4, E4, E4, E4,
            D4, D4, E4, D4, C4
    };
    std::vector<float> active_frequencies;
    if (melody == 0)
        active_frequencies = frequencies1;
    else if (melody == 1)
        active_frequencies = frequencies2;
    else {
        qDebug() << "Unknown melody: " << melody;
        return;
    }
    std::thread playThread([active_frequencies](){
        for (const auto &frequency: active_frequencies){
            SoundManager::get_instance().add_note(frequency);
            std::this_thread::sleep_for(std::chrono::milliseconds(450));
            SoundManager::get_instance().remove_note(frequency);
        }
    });
    playThread.detach();
}







