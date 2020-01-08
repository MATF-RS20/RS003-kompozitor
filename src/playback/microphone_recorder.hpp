#ifndef KOMPOZITOR_MICROPHONE_RECORDER_HPP
#define KOMPOZITOR_MICROPHONE_RECORDER_HPP

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio.hpp>
#include <QtCore/QTimer>

class MicrophoneRecorder {
public:
    [[nodiscard]]
    static MicrophoneRecorder& get_instance();

    MicrophoneRecorder(const MicrophoneRecorder& other) = delete;
    MicrophoneRecorder& operator=(const MicrophoneRecorder& other) = delete;
    MicrophoneRecorder(MicrophoneRecorder&& other) = delete;
    MicrophoneRecorder& operator=(MicrophoneRecorder&& other) = delete;

    void start_recording();
    sf::SoundBuffer stop_recording();
    void save_recording(std::string file_name);

private:
    MicrophoneRecorder() = default;

    sf::SoundBufferRecorder _recorder;
    sf::SoundBuffer _buffer;
};

#endif //KOMPOZITOR_MICROPHONE_RECORDER_HPP
