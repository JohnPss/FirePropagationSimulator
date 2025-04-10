#pragma once

#include <queue>
#include <vector>
#include <utility>
#include "MatrixStruct.hpp"

using namespace std;

struct MatrixStruct;

class Fire
{
private:
    MatrixStruct *m;
    int centerX;
    int centerY;

    queue<pair<int, int>> currentBurning;

    vector<pair<int, int>> burningCells;

    vector<pair<int, int>> nextToBurn;

    bool isValidBurnableCell(int x, int y) const;

public:
    Fire(MatrixStruct *matrix);
    bool doIt();
    void spreadFire();
    void updateBurningCells();
};
