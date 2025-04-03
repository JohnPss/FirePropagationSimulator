#pragma once

#include "MatrixStruct.hpp"
#include "iostream"
#include "Util.hpp"
#include "Forest.hpp"
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>

#include <vector>
using namespace std;

class Animal
{
private:
    static int counter;

public:
    int x, y;
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

    void findFirstSafePlace(MatrixStruct *m);
    void moveAnimal(MatrixStruct *m);
    bool countThreeTimes();
    void resetCounter();
};