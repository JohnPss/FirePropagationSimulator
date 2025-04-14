#include "Fire.hpp"
#include "Config.hpp"
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <string>

using namespace std;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

Fire::Fire(MatrixStruct *matrix) : m(matrix)
{
    centerX = m->initial_x; // Correção do typo (intial_x -> initial_x)
    centerY = m->initial_y;

    currentBurning.push(make_pair(centerX, centerY));

    if (WIND_ENABLED)
    {
        cout << "Wind is enabled with directions: ";
        string directions[4] = {"North", "South", "West", "East"};
        for (int i = 0; i < 4; i++)
        {
            if (WIND_DIRECTIONS[i])
                cout << directions[i] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Wind is disabled. Fire spreads in all directions." << endl;
    }
}

bool Fire::doIt()
{
    spreadFire();
    updateBurningCells();
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

        bool isFirstStage = false;
        for (size_t i = 0; i < firstBurnStage.size(); i++)
        {
            if (firstBurnStage[i] == cell)
            {
                firstBurnStage.erase(firstBurnStage.begin() + i);
                burningCells.push_back(cell);
                isFirstStage = true;
                break;
            }
        }

        if (!isFirstStage)
        {
            firstBurnStage.push_back(cell);

            // Nova parte: Registrar direções de propagação
            for (int i = 0; i < 4; i++)
            {
                if (WIND_ENABLED && !WIND_DIRECTIONS[i])
                    continue;

                int newX = cell.first + dx[i];
                int newY = cell.second + dy[i];

                if (isValidBurnableCell(newX, newY))
                {
                    m->matrix[newX][newY] = 2;
                    nextToBurn.push_back(make_pair(newX, newY));

                    // Registrar mudança no log
                    string direction;
                    switch (i)
                    {
                    case 0:
                        direction = "acima";
                        break;
                    case 1:
                        direction = "abaixo";
                        break;
                    case 2:
                        direction = "esquerda";
                        break;
                    case 3:
                        direction = "direita";
                        break;
                    }
                    changeLog.push_back(
                        "(" + to_string(newX) + "," + to_string(newY) +
                        ") vira 2 (" + direction + ")");
                }
            }
        }
    }
}

void Fire::updateBurningCells()
{
    for (const auto &cell : burningCells)
    {
        m->matrix[cell.first][cell.second] = 3;
    }
    burningCells.clear();

    for (const auto &cell : firstBurnStage)
    {
        currentBurning.push(cell);
    }

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
            m->matrix[x][y] == 1);
}

// Novo método para obter e limpar o log
vector<string> Fire::getChangeLog()
{
    vector<string> logs = changeLog;
    changeLog.clear();
    return logs;
}