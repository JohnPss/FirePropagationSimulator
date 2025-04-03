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
public:
    static int counter;
    MatrixStruct *m;

    vector<vector<bool>> boolMatrix;
    int x,
        y;
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

    Animal(MatrixStruct *matrix)
    {
        m = matrix;
        counter = 0;
        findFirstSafePlace();
        boolMatrix.resize(matrix->rows, vector<bool>(matrix->columns, false));
    }

    void findFirstSafePlace();
    void moveAnimal();
    bool countThreeTimes();
    void resetCounter();
    void printBoolMatrix();
};