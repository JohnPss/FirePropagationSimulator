#include "Fire.hpp"
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <string>
using namespace std;

Fire::Fire(MatrixStruct *matrix)
{
    m = matrix;
    centerX = m->intial_x;
    centerY = m->initial_y;
    currentBurning.push(make_pair(centerX, centerY));
}

bool Fire::doIt()
{
    spreadFire();
    burning();
    m->printMatrix();

    return !burningCells.empty();
}

void Fire::spreadFire()
{
    if (currentBurning.empty())
    {
        cout << "No more cells burning!" << endl;
        return;
    }

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!currentBurning.empty())
    {
        pair<int, int> cell = currentBurning.front();
        currentBurning.pop();

        burningCells.push_back(cell);

        for (int i = 0; i < 4; i++)
        {
            int newX = cell.first + dx[i];
            int newY = cell.second + dy[i];

            if (isValidCell(newX, newY))
            {
                m->matrix[newX][newY] = 2;
                nextToBurn.push_back(make_pair(newX, newY));
            }
        }
    }
}

void Fire::burning()
{
    for (const auto &cell : burningCells)
    {
        m->matrix[cell.first][cell.second] = 3;
    }
    burningCells.clear();

    for (const auto &cell : nextToBurn)
    {
        currentBurning.push(cell);
    }
    nextToBurn.clear();
}

bool Fire::isValidCell(int x, int y)
{
    return (x >= 0 && x < m->rows && y >= 0 && y < m->columns && m->matrix[x][y] == 1);
}
