#include <playback/sound_manager.hpp>
#include <src/playback/record_manager.hpp>
#include "main_model.hpp"
#include "playback/playback.hpp"
#include "sample_track.hpp"
#include "playback/microphone_recorder.hpp"
#include <iostream>
#include <cmath>
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection" // Qt uses this function
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"

static float freq(float frequency, int current_octave, int fixed_octave){
    int octave_diff = current_octave - fixed_octave;
    float freq_return = frequency * static_cast<float>(pow(2,octave_diff));
    return freq_return;
}

void MainModel::playMelody(int melody) {
    Playback::play(melody);
}

void MainModel::playNote(float frequency) {
    frequency = freq(frequency,current_octave, fixed_octave);
    SoundManager::get_instance().add_note(frequency);
}

void MainModel::stopNote(float frequency) {
    frequency = freq(frequency,current_octave, fixed_octave);
    SoundManager::get_instance().remove_note(frequency);
}

void MainModel::addRecordNote(float frequency, int note_position){
    frequency = freq(frequency,current_octave, fixed_octave);
    // current octave should be 5, not 4 ??
    // TODO ask Kristina that
    int pitch = (current_octave)*13 + note_position;
    RecordManager::get_instance().add_note(frequency, pitch);
}

void MainModel::removeRecordNote(float frequency, int note_position){
    frequency = freq(frequency,current_octave, fixed_octave);
    int pitch = (current_octave)*13 + note_position;
    RecordManager::get_instance().remove_note(frequency, pitch);
}

void MainModel::startRecordingKeyboard() {
    _isRecordingKeyboard = true;
    RecordManager::get_instance().start_recording();
    emit isRecordingKeyboardChanged();
}

void MainModel::stopRecordingKeyboard(int index) {
    _isRecordingKeyboard = false;
    QList<QObject*> result = RecordManager::get_instance().stop_recording();

    if (index == -1) {
        _tracks.push_back(new NoteTrack(2, result));
    }
    else {
        _tracks[index] = new NoteTrack(2, result);
    }
    emit onTracksChanged();
    emit isRecordingKeyboardChanged();
}
void MainModel::startRecordingMicrophone() {
    _isRecordingMicrophone = true;
    MicrophoneRecorder::get_instance().start_recording();
    emit isRecordingMicrophoneChanged();
}

void MainModel::stopRecordingMicrophone(int index) {
    _isRecordingMicrophone = false;
    sf::SoundBuffer recorded_buffer = MicrophoneRecorder::get_instance().stop_recording();
    QList<double> normalized_samples;

    normalized_samples.reserve(recorded_buffer.getSampleCount());

    for (int i = 0; i < recorded_buffer.getSampleCount(); i++) {
        double normalized_sample = static_cast<double>(recorded_buffer.getSamples()[i]) / INT16_MAX;
        normalized_samples.push_back(normalized_sample);
    }

    if (index == -1) {
        _tracks.push_back(new SampleTrack(1, normalized_samples));
    }
    else {
        _tracks[index] = new SampleTrack(1, normalized_samples);
    }
    emit onTracksChanged();
    emit isRecordingMicrophoneChanged();
}

QList<Track *> MainModel::tracks() const {
    return _tracks;
}

void MainModel::set_tracks(QList<Track *> tracks) {
    _tracks = std::move(tracks);
    emit onTracksChanged();
}

void MainModel::addMicrophoneTrack() {
    _tracks.push_back(new SampleTrack(1, {}));
    emit onTracksChanged();
}

void MainModel::addKeyboardTrack() {
    _tracks.push_back(new NoteTrack(2, {}));
    emit onTracksChanged();
}

void MainModel::calculateOctave(int x) {
    int stotina = x / 100;
    int desetica = (x / 10) % 10;
    if (stotina != 4 && stotina != 5)
        current_octave = stotina;
    else if (stotina == 5)
        current_octave = 6;
    else if (desetica >= 9) {
        current_octave = 5;
    }else {
        current_octave = 4;
    }
    current_octave += 1;
}

void MainModel::saveKeyboardComposition() {
    RecordManager::get_instance().save_composition();
}

void MainModel::saveMicrophoneComposition() {
    MicrophoneRecorder::get_instance().save_recording();
}



