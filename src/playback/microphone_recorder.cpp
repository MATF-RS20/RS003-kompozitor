#include "microphone_recorder.hpp"
#include <iostream>
#include <chrono>

MicrophoneRecorder &MicrophoneRecorder::get_instance() {
    static MicrophoneRecorder instance;
    return instance;
}

void MicrophoneRecorder::record() {
    recorder.start();

    auto time = std::chrono::system_clock::now();
    auto t_time = std::chrono::system_clock::to_time_t(time);
    std::cout << std::ctime(&t_time) << std::endl;
}

sf::SoundBuffer MicrophoneRecorder::record_stop() {
    recorder.stop();
    sf::SoundBuffer buffer = recorder.getBuffer();
    buffer.saveToFile("recorded_by_microphone.ogg");
    return buffer;
}
