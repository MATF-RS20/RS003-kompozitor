#include <playback/sound_manager.hpp>
#include <src/playback/record_manager.hpp>
#include "main_model.hpp"
#include "playback/playback.hpp"
#include "sample_track.hpp"
#include <iostream>
#include <cmath>
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection" // Qt uses this function
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"

static float freq(float frequency, int current_octave, int fixed_octave){
    int octave_diff = current_octave - fixed_octave;
    float freq_return = frequency * pow(2,octave_diff);
    //std::cout << freq_return << std::endl;
    return freq_return;
}

void MainModel::playMelody1() {
    Playback::play();
}

void MainModel::recordSomething() {
    Playback::record();
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

void MainModel::startRecording() {
    _isRecording = true;
    RecordManager::get_instance().start_recording();
    emit isRecordingChanged();
}

void MainModel::stopRecording() {
    _isRecording = false;
    std::vector<TrackNote*> result = RecordManager::get_instance().stop_recording();

    // TODO TrackNote* must be transformed to fit into Track class
    emit isRecordingChanged();
}

QList<Track *> MainModel::tracks() const {
    return _tracks;
}

void MainModel::set_tracks(QList<Track *> tracks) {
    _tracks = std::move(tracks);
    emit onTracksChanged();
}

void MainModel::addMicrophoneTrack() {
    _tracks.push_back(new SampleTrack(3, {}));
    emit onTracksChanged();
}

void MainModel::addKeyboardTrack() {
    _tracks.push_back(new NoteTrack(2, {
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
    //std::cout << current_octave << std::endl;

}

void MainModel::calculateOctave(int x) {
    //TODO on half of octave change current octave
    //std::cout << x << std::endl;
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
    //std::cout << current_octave << std::endl;
}


