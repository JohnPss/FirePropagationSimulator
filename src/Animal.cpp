#include "Animal.hpp"

int Animal::counter = 0;

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

// void Animal::moveAnimal(MatrixStruct *m)
// {
//     int ht = -1, t, tx, ty;
//     for (int i = 0; i < 4; i++)
//     {

//         t = m->matrix[x + dx[i]][y + dy[i]];

//         if (prior[t] > ht)
//         {
//             ht = prior[t];
//             tx = x + dx[i];
//             ty = y + dy[i];
//         }
//     }

//     // cout << "Moving to (" << tx << ", " << ty << ")" << endl;

//     // m->printMatrix();
//     cout << endl;
//     m->matrix[x][y] = 0;
//     x = tx;
//     y = ty;
//     m->matrix[x][y] = 2;
//     cout << "Animal moved to (" << x << ", " << y << ")" << endl;
//     m->printMatrix();
// }

void Animal::moveAnimal(MatrixStruct *m)
{
    if (m->matrix[x][y] == 0)
    {
        if (countThreeTimes())
        {
            cout << "Dint move, thats zero" << endl;
            return;
        }
    }

    resetCounter();
    int highestPriority = -1;
    vector<pair<int, int>> candidateCells;

    for (int i = 0; i < 4; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];

        {
            if (newX >= 0 && newX < m->rows && newY >= 0 && newY < m->columns)
            {
                int cellType = m->matrix[newX][newY];

                if (cellType != 2)
                {
                    int currentPriority;

                    if (cellType == 4)
                        currentPriority = 3;
                    else if (cellType == 0 || cellType == 1)
                        currentPriority = 2;
                    else if (cellType == 3)
                        currentPriority = 1;
                    else
                        currentPriority = -1;

                    if (currentPriority > highestPriority)
                    {
                        highestPriority = currentPriority;
                        candidateCells.clear();
                        candidateCells.push_back(make_pair(newX, newY));
                    }
                    else if (currentPriority == highestPriority)
                    {
                        candidateCells.push_back(make_pair(newX, newY));
                    }
                }
            }
        }
    }

    if (!candidateCells.empty())
    {
        int randomIndex = rand() % candidateCells.size();
        int newX = candidateCells[randomIndex].first;
        int newY = candidateCells[randomIndex].second;

        if (m->matrix[newX][newY] == 4)
        {
            m->matrix[newX][newY] = 0;

            convertWaterToForest(m, newX, newY);
        }

        x = newX;
        y = newY;
        // m->printMatrix();
        cout << "Animal moved to (" << x << ", " << y << ")" << endl;
    }
    else
    {
        cout << "Animal cannot move! Trapped at (" << x << ", " << y << ")" << endl;
    }
}

bool Animal::countThreeTimes()
{
    if (counter < 3)
    {
        counter++;
        return true;
    }
    return false;
}

void Animal::resetCounter()
{
    counter = 0;
}