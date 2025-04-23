#pragma once

#include "MatrixStruct.hpp"
#include "FileReaderAndWriter.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

enum TerrainState
{
    EMPTY = 0,
    TREE = 1,
    BURNING = 2,
    BURNT = 3,
    WATER = 4
};

enum MovePriority
{
    NONE = 0,
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};

class Animal
{
private:
    MatrixStruct *m;
    int x, y;
    static int stayCounter;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    vector<vector<int>> animalPath;
    vector<pair<int, int>> pathSequence;

    void findFirstSafePlace();
    bool shouldStayInEmptyArea();
    void resetStayCounter();
    void convertWaterToForest(int x, int y);
    void recordPosition();
    int getCellPriority(int cellType);

public:
    int waterFound;
    int steps;
    int deathIteration;

    Animal(MatrixStruct *matrix);
    ~Animal();
    bool moveAnimal();
    bool isInDanger();
    bool tryToEscape();
    void recordStatus(int iteration);
    void savePathMap();
    void recordDeath(int iteration);

    pair<int, int> getPosition()
    {
        return make_pair(x, y);
    }
};