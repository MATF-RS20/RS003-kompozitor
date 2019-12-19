#include <playback/sound_manager.hpp>
#include <src/playback/record_manager.hpp>
#include <utility>
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

void MainModel::startRecording() {
    _isRecording = true;
    RecordManager::get_instance().start_recording();
    emit isRecordingChanged();
}

void MainModel::stopRecording() {
    _isRecording = false;
    RecordManager::get_instance().stop_recording();
    emit isRecordingChanged();
}

QList<QObject *> MainModel::trackNotes() const {
    return _trackNotes;
}

void MainModel::setTrackNotes(QList<QObject *> trackNotes) {
    _trackNotes = std::move(trackNotes);
    emit trackNotesChanged();
}