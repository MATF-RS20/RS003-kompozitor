#include "sound_manager.hpp"

SoundManager &SoundManager::get_instance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::add_note(double freq) {
    current_active.push_back(freq);
}
