#include "Animal.hpp"

int Animal::counter = 0;

void Animal::findFirstSafePlace()
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->columns; j++)
        {
            if (m->matrix[i][j] == 1)
            {
                x = i;
                y = j;
                cout << "Safe place found at (" << x << ", " << y << ")" << endl;
                return;
            }
        }
    }
}

void Animal::moveAnimal()
{
    if (m->matrix[x][y] == 0)
    {
        if (countThreeTimes())
        {
            cout << "Dint move, thats zero" << endl;
            return;
        }
    }
    steps++;
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
            waterFind++;

            convertWaterToForest(newX, newY);
        }

        x = newX;
        y = newY;
        // animalLocationOnMatrix();
        // m->printMatrix();
        cout
            << "Animal moved to (" << x << ", " << y << ")" << endl;
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

void Animal::animalLocationOnMatrix()
{
    animalLocation[x][y] = 2;
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->columns; j++)
        {
            cout << animalLocation[i][j] << " ";
        }
        cout << endl;
    }
}

void Animal::convertWaterToForest(int x, int y)
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

bool Animal::checkSurvival()
{
    if (m->matrix[x][y] == 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Animal::giveSecondChance()
{
    moveAnimal();
}