#pragma once

#include "MatrixStruct.hpp"
#include "iostream"
#include "Util.hpp"
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
    int x, y;
    int waterFind = 0, steps = 0;
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

    vector<vector<int>> animalLocation;

    Animal(MatrixStruct *matrix)
    {
        m = matrix;
        counter = 0;
        findFirstSafePlace();
        animalLocation.resize(m->rows, vector<int>(m->columns, 0));
    }

    void moveAnimal();
    void findFirstSafePlace();
    bool countThreeTimes();
    void resetCounter();
    void animalLocationOnMatrix();
    void convertWaterToForest(int x, int y);
    bool checkSurvival();
    void giveSecondChance();
};