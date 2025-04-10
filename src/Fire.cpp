#include "Fire.hpp"
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <string>

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

enum CellState
{
    EMPTY = 0,
    BURNABLE = 1,
    BURNING = 2,
    BURNT = 3
};

Fire::Fire(MatrixStruct *matrix) : m(matrix)
{
    centerX = m->intial_x;
    centerY = m->initial_y;

    currentBurning.push(make_pair(centerX, centerY));
}

bool Fire::doIt()
{
    spreadFire();
    updateBurningCells();
    m->printMatrix();

    return !currentBurning.empty();
}

void Fire::spreadFire()
{
    if (currentBurning.empty())
    {
        cout << "No more cells burning!" << endl;
        return;
    }

    while (!currentBurning.empty())
    {
        pair<int, int> cell = currentBurning.front();
        currentBurning.pop();

        burningCells.push_back(cell);

        for (int i = 0; i < 4; i++)
        {
            int newX = cell.first + dx[i];
            int newY = cell.second + dy[i];

            if (isValidBurnableCell(newX, newY))
            {
                m->matrix[newX][newY] = BURNING;
                nextToBurn.push_back(make_pair(newX, newY));
            }
        }
    }
}

void Fire::updateBurningCells()
{
    for (const auto &cell : burningCells)
    {
        m->matrix[cell.first][cell.second] = BURNT;
    }
    burningCells.clear();

    for (const auto &cell : nextToBurn)
    {
        currentBurning.push(cell);
    }
    nextToBurn.clear();
}

bool Fire::isValidBurnableCell(int x, int y) const
{
    return (x >= 0 && x < m->rows &&
            y >= 0 && y < m->columns &&
            m->matrix[x][y] == BURNABLE);
}