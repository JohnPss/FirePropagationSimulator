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
                cout << "Safe place found at (" << x << ", " << y << ")" << endl;
                return;
            }
        }
    }
}