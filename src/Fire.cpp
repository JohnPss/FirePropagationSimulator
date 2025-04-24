#include "Fire.hpp"
#include <string>

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

    std::string getDirectionName(int dir)
    {
        switch (dir)
        {
        case NORTH:
            return "acima";
        case SOUTH:
            return "abaixo";
        case WEST:
            return "esquerda";
        case EAST:
            return "direita";
        default:
            return "desconhecida";
        }
    }
}

Fire::Fire(MatrixStruct *matrix) : m(matrix)
{
    burningQueue.push({m->initial_x, m->initial_y});
    logStateChange(m->initial_x, m->initial_y, 2);
}

bool Fire::spreadIteration()
{
    if (burningQueue.empty())
        return false;

    while (!burningQueue.empty())
    {
        auto [x, y] = burningQueue.front();
        burningQueue.pop();

        m->matrix[x][y] = 3;
        logStateChange(x, y, 3);

        processSpread(x, y);
    }

    burningQueue = std::queue<std::pair<int, int>>();
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

void Fire::logStateChange(int x, int y, int newState, const std::string &direction)
{
    std::string logEntry = "(" + std::to_string(x) + "," + std::to_string(y) + ") vira " + std::to_string(newState);
    if (!direction.empty())
    {
        logEntry += " (" + direction + ")";
    }
    changeLog.push_back(logEntry);
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
            logStateChange(newX, newY, 2, getDirectionName(dir));
        }
    }
}

std::vector<std::string> Fire::getChanges()
{
    std::vector<std::string> logs;
    swap(logs, changeLog);
    return logs;
}