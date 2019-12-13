#ifndef KOMPOZITOR_SOUND_MANAGER_HPP
#define KOMPOZITOR_SOUND_MANAGER_HPP

#include <vector>

class SoundManager {
public:
    [[nodiscard]]
    static SoundManager& get_instance();

    SoundManager(const SoundManager& other) = delete;
    SoundManager& operator=(const SoundManager& other) = delete;
    SoundManager(SoundManager&& other) = delete;
    SoundManager& operator=(SoundManager&& other) = delete;

    void add_note(double freq);
private:
    SoundManager() = default;
    std::vector<double> current_active;
};

#endif //KOMPOZITOR_SOUND_MANAGER_HPP
