#include "sound_manager.hpp"
#include "playback.hpp"

SoundManager &SoundManager::get_instance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::add_note(double freq) {
    current_active.insert(freq);
    play_notes();
}

void SoundManager::remove_note(double freq) {
    current_active.erase(freq);
    play_notes();
}

void SoundManager::play_notes() {
    if (!current_active.empty()) {
        std::vector<sf::Int16> buffer_data = Playback::buffer_data_from_multiple_notes(current_active);

        soundBuffer.loadFromSamples(&buffer_data[0], buffer_data.size(), 1, 44100);

        sound.play();
    } else {
        sound.stop();
    }
}
