#include "FileReaderAndWriter.hpp"
#include <iostream>

ofstream FileReader::outputStream;

MatrixStruct *readFile()
{
    ifstream inputFile("input.dat");
    MatrixStruct *matStruct = (MatrixStruct *)malloc(sizeof(matStruct));

    if (!inputFile.is_open())
    {
        cerr << "Erro ao abrir o arquivo" << endl;
        return NULL;
    }

    inputFile >> matStruct->rows >> matStruct->columns >> matStruct->initial_x >> matStruct->initial_y;
    matStruct->mallocMatrix();

    for (int i = 0; i < matStruct->rows; i++)
    {
        for (int j = 0; j < matStruct->columns; j++)
        {
            inputFile >> matStruct->matrix[i][j];
        }
    }

    return matStruct;
}

void FileReader::openOutputFile()
{
    outputStream.open("output.dat");
    if (!outputStream.is_open())
    {
        cerr << "Erro ao abrir o arquivo de saída" << endl;
    }
}

void FileReader::writeToOutput(const string &message)
{
    if (outputStream.is_open())
    {
        outputStream << message << endl;
    }
}

void FileReader::closeOutputFile()
{
    if (outputStream.is_open())
    {
        outputStream.close();
    }
}