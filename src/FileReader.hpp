#pragma once
#include "MatrixStruct.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class FileReader
{
public:
    MatrixStruct *readFile();
};