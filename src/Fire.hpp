#pragma once
#include <queue>
#include <vector>
#include "MatrixStruct.hpp"
// #include "config.hpp"
using namespace std;

class Fire
{
public:
    int centerX, centerY;
    MatrixStruct *m;
    queue<pair<int, int>> currentBurning;
    vector<pair<int, int>> nextToBurn;
    vector<pair<int, int>> burningCells;

    Fire(MatrixStruct *matrix);
    void spreadFire();
    void burning();
    bool isValidCell(int x, int y);
    bool doIt();
};