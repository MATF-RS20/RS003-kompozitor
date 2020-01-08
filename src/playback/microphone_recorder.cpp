#include "microphone_recorder.hpp"
#include <iostream>
#include <chrono>

MicrophoneRecorder &MicrophoneRecorder::get_instance() {
    static MicrophoneRecorder instance;
    return instance;
}

void MicrophoneRecorder::start_recording() {
    _recorder.start();

    auto time = std::chrono::system_clock::now();
    auto t_time = std::chrono::system_clock::to_time_t(time);
    std::cout << std::ctime(&t_time) << std::endl;
}

sf::SoundBuffer MicrophoneRecorder::stop_recording() {
    _recorder.stop();
    sf::SoundBuffer buffer = _recorder.getBuffer();
    //TODO za sada se odmah cuva snimak sa mikrofona u fajl
//    buffer.saveToFile("recorded_by_microphone.ogg");
    return buffer;
}

void MicrophoneRecorder::save_recording(std::string file_name) {
    sf::SoundBuffer buffer = _recorder.getBuffer();
    buffer.saveToFile(file_name);
}

