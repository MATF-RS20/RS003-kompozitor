#include "microphone_recorder.hpp"

MichrophoneRecorder &MichrophoneRecorder::get_instance() {
    static MichrophoneRecorder instance;
    return instance;
}

