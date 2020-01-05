#ifndef KOMPOZITOR_RECORD_MANAGER_HPP
#define KOMPOZITOR_RECORD_MANAGER_HPP

#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <src/ui_model/track_note.hpp>
#include "playback.hpp"
#include "sound_manager.hpp"

enum State {
    UP,
    DOWN
};

struct NoteEvent {
    double freq = 0.0;
    std::chrono::time_point<std::chrono::system_clock> note_time_point;
    State current_state;
    int pitch;
};

class RecordManager {
public:
    [[nodiscard]]
    static RecordManager& get_instance();

    RecordManager(const RecordManager& other) = delete;
    RecordManager& operator=(const RecordManager& other) = delete;
    RecordManager(RecordManager&& other) = delete;
    RecordManager& operator=(RecordManager&& other) = delete;

    void start_recording();
    QList<QObject*> stop_recording();

    void add_note(double freq, int pitch);
    void remove_note(double freq, int pitch);

    void save_composition();

    float end_time() {
        return relative_time(_start_time, _end_time).count();
    }

    static std::chrono::duration<float> relative_time(std::chrono::time_point<std::chrono::system_clock> start_time,
                                                      std::chrono::time_point<std::chrono::system_clock> compare_time);
private:
    RecordManager() = default;

    std::vector<NoteEvent> _record_data;
    QList<QObject*> _track_final_data;
    std::vector<TrackNote*> _record_data_by_frequency;
    std::chrono::time_point<std::chrono::system_clock> _start_time;
    std::chrono::time_point<std::chrono::system_clock> _end_time;
};

#endif //KOMPOZITOR_RECORD_MANAGER_HPP
