#pragma once

#include "MatrixStruct.hpp"
#include "iostream"
#include "Util.hpp"

#include <vector>
using namespace std;

class Animal
{
public:
    int x, y;
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

    void findFirstSafePlace(MatrixStruct *m);
    void moveAnimal(MatrixStruct *m);
};