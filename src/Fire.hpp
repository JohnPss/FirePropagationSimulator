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
    queue<pair<int, int>> burningQueue;
    vector<pair<int, int>> nextSpread;
    vector<string> changeLog;

    bool isValidCell(int x, int y) const;
    void processSpread(int x, int y);

public:
    Fire(MatrixStruct *matrix);
    bool spreadIteration();
    vector<string> getChanges();
};