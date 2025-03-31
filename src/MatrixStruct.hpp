#pragma once
#include <cstdlib>
#include <iostream>
using namespace std;

typedef struct MatrixStruct
{
    int intial_x, initial_y, rows, columns;
    int **matrix;

    void mallocMatrix();
    void printMatrix();

} MatrixStruct;
