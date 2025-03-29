#include "FileReader.hpp"

MatrixStruct *FileReader::readFile()
{
    ifstream inputFile("input.dat");
    MatrixStruct *matStruct = (MatrixStruct *)malloc(sizeof(matStruct));

    if (!inputFile.is_open())
    {
        cerr << "Erro ao abrir o arquivo" << endl;
        return NULL;
    }

    inputFile >> matStruct->rows >> matStruct->columns >> matStruct->intial_x >> matStruct->initial_y;
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