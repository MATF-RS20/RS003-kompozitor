#include "sound_manager.hpp"
#include <iostream>

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

void SoundManager::play_notes() const {
    // TODO only debug output for now
    std::cout << '[';
    for (double i: current_active) {
        std::cout << i << " ";
    }
    std::cout << ']' << std::endl;
}
