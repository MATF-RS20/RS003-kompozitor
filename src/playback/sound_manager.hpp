#ifndef KOMPOZITOR_SOUND_MANAGER_HPP
#define KOMPOZITOR_SOUND_MANAGER_HPP

#include <unordered_set>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class SoundManager {
public:
    [[nodiscard]]
    static SoundManager& get_instance();

    SoundManager(const SoundManager& other) = delete;
    SoundManager& operator=(const SoundManager& other) = delete;
    SoundManager(SoundManager&& other) = delete;
    SoundManager& operator=(SoundManager&& other) = delete;

    void add_note(double freq);

    void remove_note(double freq);
    void play_sound_buffer(std::vector<sf::Int16> buffer_data);
private:
    SoundManager() {
        sound.setBuffer(soundBuffer);
        sound.setLoop(true);
    }

    void play_notes();

    std::unordered_set<double> current_active;
    sf::Sound sound;
    sf::SoundBuffer soundBuffer;
};

#endif //KOMPOZITOR_SOUND_MANAGER_HPP
