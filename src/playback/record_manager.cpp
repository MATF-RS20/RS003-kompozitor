#include <thread>
#include "record_manager.hpp"

RecordManager &RecordManager::get_instance() {
    static RecordManager instance;
    return instance;
}

std::vector<TrackNote*> RecordManager::stop_recording() {
    _end_time = std::chrono::system_clock::now();

    for (auto & i : _track_final_data){
        std::cout << "Note info:  " <<  i->pitch() << "    "
                  << i->start() << "    " << i->end() << std::endl;
    }
//    save_composition();
    return _track_final_data;
}

void RecordManager::start_recording() {
    _start_time = std::chrono::system_clock::now();
    _record_data.clear();
    _track_final_data.clear();
}

void RecordManager::add_note(double freq) {
    NoteEvent currentNote;
    currentNote.freq = freq;
    currentNote.note_time_point = std::chrono::system_clock::now();
    currentNote.current_state = DOWN;

    _record_data.push_back(currentNote);
}

void RecordManager::remove_note(double freq) {
    NoteEvent currentNote;
    currentNote.freq = freq;
    currentNote.note_time_point = std::chrono::system_clock::now();
    currentNote.current_state = UP;

    for (auto beg = _record_data.begin(); beg < _record_data.end(); beg++) {
        if (beg->freq == currentNote.freq){
            auto* tmp = new TrackNote(static_cast<int>(currentNote.freq),
                                      relative_time(_start_time, beg->note_time_point).count(),
                                      relative_time(_start_time, currentNote.note_time_point).count());

            _record_data.erase(beg);
            _track_final_data.push_back(tmp);
            break;
        }
    }
}

std::chrono::duration<float> RecordManager::relative_time(std::chrono::time_point<std::chrono::system_clock> start_time,
                                                          std::chrono::time_point<std::chrono::system_clock> compare_time) {
    auto dur =  compare_time - start_time;

    std::chrono::duration<float> f_secs{};
    f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(dur);

    return f_secs;
}

void RecordManager::save_composition() {
    float duration = end_time();
    unsigned buffer_size = duration * 44100;
    std::vector<double> raw_buffer_data(buffer_size);
    double max_amplitude = 0;


    for (auto i : _track_final_data){
        std::cout << i->end()-i->start() << std::endl;
        auto samples = Playback::create_sample(i->pitch(), i->end()-i->start(), 44100);
        int k = 0;
        for (unsigned j = 44100*i->start(); j < 44100*i->end(); j++) {
            raw_buffer_data[j] += samples[k++];
            if (abs(raw_buffer_data[j]) > max_amplitude) {
                max_amplitude = abs(raw_buffer_data[j]);
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
    sound.setBuffer(soundBuffer);

    soundBuffer.loadFromSamples(&buffer_data[0], buffer_data.size(), 1, 44100);
    soundBuffer.saveToFile("test_save_recording.ogg");

    // TODO after we add pop-up window for asking if user wants to save melody

//    testing recorded melody
//    SoundManager::get_instance().play_sound_buffer(buffer_data);
}
