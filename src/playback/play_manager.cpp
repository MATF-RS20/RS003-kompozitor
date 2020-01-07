#include "play_manager.hpp"
#include "playback.hpp"
#include "sound_manager.hpp"
#include <src/ui_model/note_track.hpp>
#include <src/ui_model/sample_track.hpp>
#include <src/ui_model/track_note.hpp>

PlayManager &PlayManager::get_instance() {
    static PlayManager instance;
    return instance;
}

void PlayManager::play(int index, Track *track) {
    if (auto *note_track = dynamic_cast<NoteTrack *>(track)){
        createKeyboardSound(index, note_track);
    } else if (auto *sample_track = dynamic_cast<SampleTrack *>(track)) {
        createVoiceSound(index, sample_track);
    }
    sound_data[index].first.setBuffer(sound_data[index].second);
    sound_data[index].first.play();
}

void PlayManager::stop(int index) {
    if(sound_data.empty()){
        return;
    }
    sound_data[index].first.setBuffer(sound_data[index].second);
    sound_data[index].first.stop();
}

float PlayManager::pitch_to_frequency(int pitch) {
    int current_octave = pitch / 13;
    int note_in_octave = pitch % 13 - 1;

    // because of "K" -> last octave note
    if (note_in_octave == -1) {
        current_octave--;
        note_in_octave = 12;
    }
    int octave_diff = current_octave - FIXED_OCTAVE;
    float freq_return = main_octave_frequencies[note_in_octave] * static_cast<float>(pow(2, octave_diff));
    return freq_return;
}

void PlayManager::createKeyboardSound(int index, NoteTrack *note_track) {
    QList<QObject *> notes_data = note_track->notes();

    if (notes_data.empty()) {
        return;
    }

    auto last_note = dynamic_cast<TrackNote*>(notes_data[notes_data.size()-1]);
    float duration = last_note->end();

    unsigned buffer_size = duration * 44100;
    std::vector<double> raw_buffer_data(buffer_size);
    double max_amplitude = - MAXFLOAT;

    for (auto note_object : notes_data) {
        TrackNote* note = static_cast<TrackNote*>(note_object);
        int pitch = note->pitch();
        float frequency = pitch_to_frequency(pitch);

        auto samples = Playback::create_sample(frequency, note->end()-note->start(), 44100);

        for (unsigned j = 0; j < samples.size(); j++) {
            raw_buffer_data[j + 44100 * note->start()] += samples[j];
            if (abs(raw_buffer_data[j + 44100 * note->start()]) > max_amplitude) {
                max_amplitude = abs(raw_buffer_data[j + 44100 * note->start()]);
            }
        }
    }

    double amplification_ratio = SHRT_MAX / max_amplitude;
    std::vector<sf::Int16> buffer_data(raw_buffer_data.size());

    for (unsigned i = 0; i < buffer_size; ++i) {
        buffer_data[i] = static_cast<sf::Int16>(raw_buffer_data[i] * amplification_ratio);
    }

    sf::Sound sound;
    sf::SoundBuffer soundBuffer;
    sound.setLoop(false);
    soundBuffer.loadFromSamples(&buffer_data[0], buffer_data.size(), 1, 44100);
    sound.setBuffer(soundBuffer);

    std::pair<sf::Sound, sf::SoundBuffer> tmp {sound, soundBuffer};
    sound_data[index] = tmp;
}

void PlayManager::createVoiceSound(int index, SampleTrack *sample_track) {
    QList<double> normalized_samples = sample_track->samples();
    QList<double> samples;

    samples.reserve(normalized_samples.size());

    for (double normalized_sample : normalized_samples) {
        double sample = normalized_sample * INT16_MAX;
        samples.push_back(sample);
    }

    std::vector<sf::Int16> buffer_data(samples.size());
    std::copy(samples.begin(),
              samples.end(),
              buffer_data.begin());

    sf::Sound sound;
    sf::SoundBuffer soundBuffer;
    sound.setLoop(false);
    soundBuffer.loadFromSamples(&buffer_data[0], buffer_data.size(), 1, 44100);
    sound.setBuffer(soundBuffer);

    std::pair<sf::Sound, sf::SoundBuffer> tmp {sound, soundBuffer};
    sound_data[index] = tmp;
}
