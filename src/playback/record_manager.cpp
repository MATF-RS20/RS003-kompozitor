#include "record_manager.hpp"

RecordManager &RecordManager::get_instance() {
    static RecordManager instance;
    return instance;
}

void RecordManager::stop_recording() {
    _end_time = std::chrono::system_clock::now();

    std::chrono::duration<float> time_diff = relative_time(_start_time, _end_time);
    float time_diff_secs = time_diff.count();
    std::cout << "End time registered: " << time_diff_secs << '\n';

//    for (int i = 0; i < _track_final_data.size(); i++){
//        std::cout << "Note info: " << _track_final_data.at(i).pitch() << std::endl;
//    }

}

void RecordManager::start_recording() {
    _start_time = std::chrono::system_clock::now();

    std::chrono::duration<float> time_diff = relative_time(_start_time, _start_time);
    float time_diff_secs = time_diff.count();
    std::cout << "Start time registered: " << time_diff_secs << '\n';
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
            TrackNote tmp(currentNote.freq,
                          relative_time(_start_time, beg->note_time_point).count(),
                          relative_time(_start_time, currentNote.note_time_point).count());

            _record_data.erase(beg);
            std::cout << "Note info:  " <<  tmp.pitch() << "    "
                      << tmp.start() << "    " << tmp.end() << std::endl;

            // TODO figure out why push_back is not working
//            _track_final_data.push_back(TrackNote(2,3,4));
            break;
        }
    }
}

std::chrono::duration<float> RecordManager::relative_time(std::chrono::time_point<std::chrono::system_clock> start_time,
                                                          std::chrono::time_point<std::chrono::system_clock> compare_time) {
    std::chrono::duration<long long int, std::__ratio_gcd<std::micro, std::micro>::type> dur{};
    dur =  compare_time - start_time;

    std::chrono::duration<float> f_secs{};
    f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(dur);

    return f_secs;
}