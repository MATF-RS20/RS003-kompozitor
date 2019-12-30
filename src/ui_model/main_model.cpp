#include <playback/sound_manager.hpp>
#include <src/playback/record_manager.hpp>
#include <utility>
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
    std::cout << freq_return << std::endl;
    return freq_return;
}

void MainModel::playMelody1() {
    Playback::play();
}

void MainModel::recordSomething() {
    std::vector<sf::Int16> recorded_samples = Playback::record();

    QList<double> normalized_samples;

    normalized_samples.reserve(recorded_samples.size());

    for (const auto &sample : recorded_samples) {
        normalized_samples.push_back(static_cast<double>(sample) / INT16_MAX);
    }

    _tracks.push_back(new SampleTrack(0, normalized_samples));
    emit onTracksChanged();
}

void MainModel::playNote(float frequency) {
    frequency = freq(frequency,current_octave, fixed_octave);
    SoundManager::get_instance().add_note(frequency);
}

void MainModel::stopNote(float frequency) {
    frequency = freq(frequency,current_octave, fixed_octave);
    SoundManager::get_instance().remove_note(frequency);
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

QList<Track *> MainModel::tracks() const {
    return _tracks;
}

void MainModel::set_tracks(QList<Track *> tracks) {
    _tracks = std::move(tracks);
    emit onTracksChanged();
}

void MainModel::addMicrophoneTrack() {
    _tracks.push_back(new SampleTrack(1, QList{0.0, 1.0, 0.0}));
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
    std::cout << current_octave << std::endl;

}


