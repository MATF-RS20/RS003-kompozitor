#include <playback/sound_manager.hpp>
#include "main_model.hpp"
#include "playback/playback.hpp"

#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection" // Qt uses this function
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"
void MainModel::playSomething() {
    Playback::play(timer);
}

void MainModel::recordSomething() {
    Playback::record();
}

void MainModel::playNote(float frequency) {
    SoundManager::get_instance().add_note(frequency);
}

void MainModel::stopNote(float frequency) {
    SoundManager::get_instance().remove_note(frequency);
}

void MainModel::MyTimerSlot() {
    Playback::my_timer_slot();
}

// For testing purposes
TrackNote* MainModel::getTrackNote() const {
    auto *track_note = new TrackNote();
    track_note->setPitch(5);
    track_note->setStart(0.1);
    track_note->setEnd(10.0);
    return track_note;
}
