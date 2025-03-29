#pragma once
#include <cstdlib>
typedef struct MatrixStruct
{
    int intial_x, initial_y, rows, columns;
    int **matrix;

    void mallocMatrix();

} MatrixStruct;
