#pragma once
#include "MatrixStruct.hpp"
#include "Config.hpp"
#include <queue>
#include <vector>
#include <utility>
#include <string>

class Fire
{
private:
    MatrixStruct *m;
    std::queue<std::pair<int, int>> burningQueue;
    std::vector<std::pair<int, int>> nextSpread;
    std::vector<std::string> changeLog;

    bool isValidCell(int x, int y) const;
    void logStateChange(int x, int y, int newState, const std::string &direction = "");
    void processSpread(int x, int y);

public:
    Fire(MatrixStruct *matrix);
    bool spreadIteration();
    std::vector<std::string> getChanges();
};