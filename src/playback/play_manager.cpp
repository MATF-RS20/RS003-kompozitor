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
//        sound_data[index].play();
        SoundManager::get_instance().play_sound_buffer(sound_data[index]);

    } else if (auto *sample_track = dynamic_cast<SampleTrack *>(track)) {
        createVoiceSound(index, sample_track);
        SoundManager::get_instance().play_sound_buffer(sound_data[index]);
    }
}

void PlayManager::stop(int index) {

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

    sound_data[index] = buffer_data;
}

void PlayManager::createVoiceSound(int index, SampleTrack *sample_track) {
    QList<double> normalized_samples = sample_track->samples();
    QList<double> samples;

    samples.reserve(normalized_samples.size());

    for (int i = 0; i < normalized_samples.size(); i++) {
        double sample = normalized_samples[i] * INT16_MAX;
        samples.push_back(sample);
    }

    std::vector<sf::Int16> buffer_data(samples.size());
    for (unsigned i = 0; i < buffer_data.size(); ++i) {
        buffer_data[i] = static_cast<sf::Int16>(samples[i]);
    }

    sound_data[index] = buffer_data;
}
