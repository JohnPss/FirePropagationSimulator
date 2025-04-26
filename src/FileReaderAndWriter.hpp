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
    static void openOutputFile();
    static void writeToOutput(const string &message);
    static void closeOutputFile();

private:
    static ofstream outputStream;
};

MatrixStruct *readFile();
