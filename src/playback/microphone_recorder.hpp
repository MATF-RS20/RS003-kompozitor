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

    void record();
    sf::SoundBuffer record_stop();


private:
    MicrophoneRecorder() = default;

    sf::Sound sound;
    sf::SoundBuffer soundBuffer;
    sf::SoundBufferRecorder recorder;
};

#endif //KOMPOZITOR_MICROPHONE_RECORDER_HPP
