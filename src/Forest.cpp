#include "Forest.hpp"

int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

void convertWaterToForest(MatrixStruct *m, int x, int y)
{
    m->matrix[x][y] = 0;

    for (int i = 0; i < 4; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (newX >= 0 && newX < m->rows && newY >= 0 && newY < m->columns)
        {
            m->matrix[newX][newY] = 1;
        }
    }
}