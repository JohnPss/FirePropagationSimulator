#pragma once

#include "MatrixStruct.hpp"
#include "TerrainEnums.hpp"
#include "FileReaderAndWriter.hpp"
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>

class Animal
{
private:
    static const int MAX_STAY_COUNT = 3;
    static const int DIRECTION_COUNT = 4;

    MatrixStruct *m;
    int x, y;
    int stayCounter;

    const int dx[DIRECTION_COUNT] = {1, -1, 0, 0};
    const int dy[DIRECTION_COUNT] = {0, 0, 1, -1};

    unordered_map<int, int> terrainPriority;

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

    void savePathMap();
    void recordDeath(int iteration);

    pair<int, int> getPosition() const { return make_pair(x, y); }
};