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
private:
    SoundManager() = default;

    void play_notes() const;

    std::unordered_set<double> current_active;
    sf::Sound sound;
    sf::SoundBuffer soundBuffer;
};

#endif //KOMPOZITOR_SOUND_MANAGER_HPP
