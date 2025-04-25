#include "Animal.hpp"

Animal::Animal(MatrixStruct *matrix)
    : m(matrix),
      stayCounter(0),
      waterFound(0),
      steps(0),
      deathIteration(-1)
{

    terrainPriority = {
        {BURNT, 0},
        {TREE, 1},
        {EMPTY, 1},
        {WATER, 2}};

    srand(static_cast<unsigned int>(time(nullptr)));

    animalPath.resize(m->rows, std::vector<int>(m->columns, 0));

    findFirstSafePlace();
    pathSequence.emplace_back(x, y);

    recordPosition();
}

Animal::~Animal()
{

    FileReader::writeToOutput("\nSumario da jornada:");

    std::string pathStr = "Caminho do animal: ";
    for (size_t idx = 0; idx < pathSequence.size(); ++idx)
    {
        if (idx > 0)
            pathStr += " -> ";
        pathStr += "(" + std::to_string(pathSequence[idx].first) + "," + std::to_string(pathSequence[idx].second) + ")";
    }
    FileReader::writeToOutput(pathStr);

    FileReader::writeToOutput("Passos totais: " + std::to_string(steps));
    FileReader::writeToOutput("Encontrou água: " + std::to_string(waterFound) + (waterFound == 1 ? " vez" : " vezes"));

    if (deathIteration > 0)
    {
        FileReader::writeToOutput("Iteração cercado: " + std::to_string(deathIteration));
        FileReader::writeToOutput("Animal sobreviveu: Não");
    }
    else
    {
        FileReader::writeToOutput("Iteração cercado: N/A");
        FileReader::writeToOutput("Animal sobreviveu: Sim");
    }
}

void Animal::findFirstSafePlace()
{
    bool found = false;

    for (int i = 0; i < m->rows && !found; i++)
    {
        for (int j = 0; j < m->columns && !found; j++)
        {
            if (m->matrix[i][j] == TREE || m->matrix[i][j] == EMPTY || m->matrix[i][j] == WATER)
            {
                x = i;
                y = j;
                found = true;
            }
        }
    }

    if (!found)
    {
        x = 0;
        y = 0;
    }
}

bool Animal::shouldStayInEmptyArea()
{
    if (m->matrix[x][y] == EMPTY)
    {
        if (stayCounter < MAX_STAY_COUNT)
        {
            stayCounter++;
            return true;
        }
    }
    return false;
}

void Animal::resetStayCounter()
{
    stayCounter = 0;
}

int Animal::getCellPriority(int cellType)
{

    auto it = terrainPriority.find(cellType);
    if (it != terrainPriority.end())
    {
        return it->second;
    }

    return 0;
}

bool Animal::moveAnimal()
{

    if (shouldStayInEmptyArea())
    {
        return true;
    }

    resetStayCounter();

    int highestPriority = -1;
    std::vector<std::pair<int, int>> candidateCells;

    for (int i = 0; i < DIRECTION_COUNT; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (newX >= 0 && newX < m->rows && newY >= 0 && newY < m->columns)
        {
            int cellType = m->matrix[newX][newY];

            if (cellType != BURNING)
            {
                int priority = getCellPriority(cellType);

                if (priority > highestPriority)
                {
                    highestPriority = priority;
                    candidateCells.clear();
                    candidateCells.push_back(std::make_pair(newX, newY));
                }
                else if (priority == highestPriority)
                {
                    candidateCells.push_back(std::make_pair(newX, newY));
                }
            }
        }
    }

    if (!candidateCells.empty())
    {
        int randomIndex = rand() % candidateCells.size();
        int newX = candidateCells[randomIndex].first;
        int newY = candidateCells[randomIndex].second;

        steps++;

        if (m->matrix[newX][newY] == WATER)
        {
            m->matrix[newX][newY] = EMPTY;
            waterFound++;
            convertWaterToForest(newX, newY);
        }

        x = newX;
        y = newY;
        pathSequence.emplace_back(x, y);
        recordPosition();

        return true;
    }
    else
    {
        return false;
    }
}

void Animal::recordPosition()
{
    animalPath[x][y]++;
}

void Animal::convertWaterToForest(int x, int y)
{
    m->matrix[x][y] = EMPTY;

    for (int i = 0; i < DIRECTION_COUNT; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (newX >= 0 && newX < m->rows && newY >= 0 && newY < m->columns)
        {
            m->matrix[newX][newY] = TREE;
        }
    }
}

bool Animal::isInDanger()
{
    return (m->matrix[x][y] == BURNING);
}

bool Animal::tryToEscape()
{
    return moveAnimal();
}

void Animal::recordDeath(int iteration)
{
    deathIteration = iteration;
}

void Animal::savePathMap()
{
    std::ofstream pathMapFile("animal_path_map.dat");

    if (pathMapFile.is_open())
    {
        std::string content = "Animal Path Frequency Map:\n";
        content += "(Higher numbers indicate more frequent visits)\n\n";

        for (int i = 0; i < m->rows; i++)
        {
            for (int j = 0; j < m->columns; j++)
            {
                if (animalPath[i][j] > 0)
                {
                    content += std::to_string(animalPath[i][j]) + " ";
                }
                else
                {
                    content += ". ";
                }
            }
            content += "\n";
        }

        pathMapFile << content;
        pathMapFile.close();
    }
    else
    {
        std::cerr << "Error: Could not save animal path map!" << std::endl;
    }
}