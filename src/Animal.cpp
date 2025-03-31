#include "Animal.hpp"

void Animal::findFirstSafePlace(MatrixStruct *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->columns; j++)
        {
            if (m->matrix[i][j] == 0)
            {
                x = i;
                y = j;
                // cout << "Safe place found at (" << x << ", " << y << ")" << endl;
                return;
            }
        }
    }
}

void Animal::moveAnimal(MatrixStruct *m)
{
    int ht = -1, t, tx, ty;
    for (int i = 0; i < 4; i++)
    {

        t = m->matrix[x + dx[i]][y + dy[i]];

        if (prior[t] > ht)
        {
            ht = prior[t];
            tx = x + dx[i];
            ty = y + dy[i];
        }
    }

    // cout << "Moving to (" << tx << ", " << ty << ")" << endl;

    // m->printMatrix();
    cout << endl;
    m->matrix[x][y] = 0;
    x = tx;
    y = ty;
    m->matrix[x][y] = 2;
    // m->printMatrix();
}