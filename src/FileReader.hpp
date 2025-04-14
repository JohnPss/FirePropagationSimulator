#pragma once
#include "MatrixStruct.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

MatrixStruct *readFile();
ofstream outPutFile();
// void writeToOutputFile(MatrixStruct *m, int iteration);
