#ifndef KOMPOZITOR_MICROPHONE_RECORDER_HPP
#define KOMPOZITOR_MICROPHONE_RECORDER_HPP

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class MichrophoneRecorder {
public:
    [[nodiscard]]
    static MichrophoneRecorder& get_instance();

    MichrophoneRecorder(const MichrophoneRecorder& other) = delete;
    MichrophoneRecorder& operator=(const MichrophoneRecorder& other) = delete;
    MichrophoneRecorder(MichrophoneRecorder&& other) = delete;
    MichrophoneRecorder& operator=(MichrophoneRecorder&& other) = delete;

private:
    MichrophoneRecorder();
};

#endif //KOMPOZITOR_MICROPHONE_RECORDER_HPP
