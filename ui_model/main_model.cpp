#include <iostream>
#include "main_model.hpp"
#include "playback/playback.hpp"

#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection" // Qt uses this function
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"
void MainModel::playSomething() {
    Playback::play();
}

#include "main_model.hpp"
