#include "Fire.hpp"
#include <string>
#include <set>

namespace
{
    enum Direction
    {
        NORTH,
        SOUTH,
        WEST,
        EAST
    };
    constexpr int dx[] = {-1, 1, 0, 0};
    constexpr int dy[] = {0, 0, -1, 1};
}

Fire::Fire(MatrixStruct *matrix) : m(matrix)
{
    burningQueue.push({m->initial_x, m->initial_y});
}

bool Fire::spreadIteration()
{
    if (burningQueue.empty())
        return false;

    static set<pair<int, int>> secondBurn;
    set<pair<int, int>> toProcessAgain;

    while (!burningQueue.empty())
    {
        auto [x, y] = burningQueue.front();
        burningQueue.pop();

        if (secondBurn.find({x, y}) == secondBurn.end())
        {
            m->matrix[x][y] = 2;
            secondBurn.insert({x, y});
            toProcessAgain.insert({x, y});

            processSpread(x, y);
        }
        else
        {
            m->matrix[x][y] = 3;
            secondBurn.erase({x, y});
        }
    }

    for (const auto &cell : toProcessAgain)
    {
        burningQueue.push(cell);
    }

    for (auto &cell : nextSpread)
    {
        burningQueue.push(cell);
    }
    nextSpread.clear();

    return !burningQueue.empty();
}

bool Fire::isValidCell(int x, int y) const
{
    return x >= 0 && x < m->rows &&
           y >= 0 && y < m->columns &&
           m->matrix[x][y] == 1;
}

void Fire::processSpread(int x, int y)
{
    for (int dir = 0; dir < 4; dir++)
    {
        if (WIND_ENABLED && !WIND_DIRECTIONS[dir])
            continue;

        int newX = x + dx[dir];
        int newY = y + dy[dir];

        if (isValidCell(newX, newY))
        {
            m->matrix[newX][newY] = 2;
            nextSpread.emplace_back(newX, newY);
        }
    }
}

vector<string> Fire::getChanges()
{
    vector<string> logs;
    swap(logs, changeLog);
    return logs;
}