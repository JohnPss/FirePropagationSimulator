#include "FileReader.hpp"

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

// void writeToOutputFile(MatrixStruct *m, int iteration)
// {
//     ofstream outputFile;
//     if (iteration == 1)
//         outputFile.open("output.dat");
//     else
//         outputFile.open("output.dat", ios::app);

//     outputFile << "Iteração " << iteration << ":" << endl;
//     for (int i = 0; i < m->rows; i++)
//     {
//         for (int j = 0; j < m->columns; j++)
//         {
//             outputFile << m->matrix[i][j] << " ";
//         }
//         outputFile << endl;
//     }
//     outputFile << endl;
//     outputFile.close();
// }

ofstream outPutFile()
{
    ofstream outputFile("output.dat");
    if (!outputFile.is_open())
    {
        cerr << "Erro ao abrir o arquivo de saída" << endl;
        return ofstream();
    }

    return outputFile;
}