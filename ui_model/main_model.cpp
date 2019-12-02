#include <iostream>
#include "main_model.hpp"

#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection" // Qt uses this function
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"
void MainModel::printSomething() {
    std::cout << "Printed something from the model" << std::endl;
}

#include "main_model.hpp"
