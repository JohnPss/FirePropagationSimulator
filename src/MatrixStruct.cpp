#include "MatrixStruct.hpp"

void MatrixStruct::mallocMatrix()
{
    matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL)
    {
        free(matrix);
        exit(1);
    }

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(columns * sizeof(int));
        if (matrix[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            exit(1);
        }
    }
}