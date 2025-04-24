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
    // Constants
    static const int MAX_STAY_COUNT = 3;
    static const int DIRECTION_COUNT = 4;

    // Core data
    MatrixStruct *m;
    int x, y;
    int stayCounter;

    // Direction arrays
    const int dx[DIRECTION_COUNT] = {1, -1, 0, 0};
    const int dy[DIRECTION_COUNT] = {0, 0, 1, -1};

    // Priority map - maps terrain type to priority
    std::unordered_map<int, int> terrainPriority;

    // Path tracking
    std::vector<std::vector<int>> animalPath;
    std::vector<std::pair<int, int>> pathSequence;

    // Helper methods
    void findFirstSafePlace();
    bool shouldStayInEmptyArea();
    void resetStayCounter();
    void convertWaterToForest(int x, int y);
    void recordPosition();
    int getCellPriority(int cellType);
    void initializePriorityMap();

public:
    // Statistics
    int waterFound;
    int steps;
    int deathIteration;

    // Constructor & Destructor
    Animal(MatrixStruct *matrix);
    ~Animal();

    // Movement methods
    bool moveAnimal();
    bool isInDanger();
    bool tryToEscape();

    // Logging methods
    void recordStatus(int iteration);
    void savePathMap();
    void recordDeath(int iteration);

    // Accessor
    std::pair<int, int> getPosition() const { return std::make_pair(x, y); }
};