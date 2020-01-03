#include <playback/sound_manager.hpp>
#include <src/playback/record_manager.hpp>
#include "main_model.hpp"
#include "playback/playback.hpp"
#include "playback/microphone_recorder.hpp"
#include <iostream>
#include <cmath>
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection" // Qt uses this function
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"

static float freq(float frequency, int current_octave, int fixed_octave){
    int octave_diff = current_octave - fixed_octave;
    float freq_return = frequency * pow(2,octave_diff);
    return freq_return;
}

void MainModel::playMelody1() {
    Playback::play();
}

void MainModel::recordSomething() {
    MicrophoneRecorder::get_instance().record();
}

void MainModel::playNote(float frequency) {
    frequency = freq(frequency,current_octave, fixed_octave);
    SoundManager::get_instance().add_note(frequency);
}

void MainModel::stopNote(float frequency) {
    frequency = freq(frequency,current_octave, fixed_octave);
    SoundManager::get_instance().remove_note(frequency);
}

void MainModel::addRecordNote(float frequency){
    frequency = freq(frequency,current_octave, fixed_octave);
    RecordManager::get_instance().add_note(frequency);
}

void MainModel::removeRecordNote(float frequency){
    frequency = freq(frequency,current_octave, fixed_octave);
    RecordManager::get_instance().remove_note(frequency);
}

void MainModel::startRecordingKeyboard() {
    _isRecordingKeyboard = true;
    RecordManager::get_instance().start_recording();
    emit isRecordingKeyboardChanged();
}

void MainModel::stopRecordingKeyboard() {
    _isRecordingKeyboard = false;
    std::vector<TrackNote*> result = RecordManager::get_instance().stop_recording();

    // TODO TrackNote* must be transformed to fit into Track class
    emit isRecordingKeyboardChanged();
}

QList<Track *> MainModel::tracks() const {
    return _tracks;
}

void MainModel::set_tracks(QList<Track *> tracks) {
    _tracks = std::move(tracks);
    emit onTracksChanged();
}

void MainModel::addMicrophoneTrack() {
    _tracks.push_back(new Track(2, Track::MICROPHONE, {
            new TrackNote(3, 0, 2),
            new TrackNote(10, 0, 3),
            new TrackNote(7, 4, 10),
    }));
    emit onTracksChanged();
}

void MainModel::addKeyboardTrack() {
    _tracks.push_back(new Track(2, Track::KEYBOARD, {
            new TrackNote(3, 0, 2),
            new TrackNote(10, 0, 3),
            new TrackNote(7, 4, 10),
    }));
    emit onTracksChanged();
}

void MainModel::octaveChanged(QString octave) {
    std::string octaveString = octave.toStdString();

    if (!std::isdigit(octaveString[0])) {
        std::cout << "Non valid entry!" << std::endl;
        return;
    }
    int octaveNumber = std::stoi(octaveString);
    if (octaveNumber < 0 || octaveNumber > 8) {
        std::cout << "Non valid entry!" << std::endl;
        return;
    }
    current_octave = octaveNumber;
}

void MainModel::calculateOctave(int x) {
    int stotina = x / 100;
    int desetica = (x / 10) % 10;
    if (stotina != 4 && stotina != 5)
        current_octave = stotina;
    else if (stotina == 5)
        current_octave = 6;
    else if (stotina == 4 && desetica >= 9){
        current_octave = 5;
    }else{
        current_octave = 4;
    }
    current_octave += 1;
}


