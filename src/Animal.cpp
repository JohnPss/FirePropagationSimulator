#include "Animal.hpp"

int Animal::stayCounter = 0;

Animal::Animal(MatrixStruct *matrix) : m(matrix), waterFound(0), steps(0), deathIteration(-1)
{
    srand(time(NULL));
    findFirstSafePlace();
    pathSequence.emplace_back(x, y);
    animalPath.resize(m->rows, vector<int>(m->columns, 0));

    FileReader::writeToOutput("Animal journey log:");
    FileReader::writeToOutput("Starting position: (" + std::to_string(x) + ", " + std::to_string(y) + ")");

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

    // Substituir escritas diretas por chamadas à FileReader
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
            if (m->matrix[i][j] == TREE || m->matrix[i][j] == EMPTY)
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
        if (stayCounter < 3)
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
    switch (cellType)
    {
    case WATER:
        return HIGH;
    case EMPTY:
        return MEDIUM;
    case TREE:
        return MEDIUM;
    case BURNT:
        return LOW;
    default:
        return NONE;
    }
}

bool Animal::moveAnimal()
{
    if (shouldStayInEmptyArea())
    {
        FileReader::writeToOutput("\nDecision: Stayed in empty area");
        return true;
    }

    resetStayCounter();

    int highestPriority = -1;
    vector<pair<int, int>> candidateCells;

    for (int i = 0; i < 4; i++)
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
                    candidateCells.push_back(make_pair(newX, newY));
                }
                else if (priority == highestPriority)
                {
                    candidateCells.push_back(make_pair(newX, newY));
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
        FileReader::writeToOutput("Step " + std::to_string(steps) + ": Moving to (" + std::to_string(newX) + ", " + std::to_string(newY) + ")");

        // Verifica se encontrou água
        if (m->matrix[newX][newY] == WATER)
        {
            m->matrix[newX][newY] = EMPTY;
            waterFound++;
            convertWaterToForest(newX, newY);
            FileReader::writeToOutput(" - Found water! Total found: " + std::to_string(waterFound));
        }

        x = newX;
        y = newY;
        pathSequence.emplace_back(x, y);
        recordPosition();

        return true;
    }
    else
    {
        FileReader::writeToOutput("WARNING: Animal trapped at (" + std::to_string(x) + ", " + std::to_string(y) + ")");
        FileReader::writeToOutput("WARNING: Animal trapped at (" + std::to_string(x) + ", " + std::to_string(y) + ")");

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

    FileReader::writeToOutput("Converting surrounding cells to forest around (" + std::to_string(x) + ", " + std::to_string(y) + ")");

    for (int i = 0; i < 4; i++)
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
    FileReader::writeToOutput("EMERGENCY: Animal in danger! Trying to escape...");

    return moveAnimal();
}

void Animal::savePathMap()
{
    ofstream pathMapFile("animal_path_map.dat");

    if (pathMapFile.is_open())
    {
        pathMapFile << "Animal Path Frequency Map:" << endl;
        pathMapFile << "(Higher numbers indicate more frequent visits)" << endl
                    << endl;

        for (int i = 0; i < m->rows; i++)
        {
            for (int j = 0; j < m->columns; j++)
            {
                if (animalPath[i][j] > 0)
                {
                    pathMapFile << animalPath[i][j] << " ";
                }
                else
                {
                    pathMapFile << ". ";
                }
            }
            pathMapFile << endl;
        }

        pathMapFile.close();
    }
    else
    {
        cerr << "Error: Could not save animal path map!" << endl;
    }
}

void Animal::recordDeath(int iteration)
{
    deathIteration = iteration;
    FileReader::writeToOutput("DEATH: Animal died at iteration " + std::to_string(iteration) + " at position (" + std::to_string(x) + ", " + std::to_string(y) + ")");
}
void Animal::recordStatus(int iteration)
{
    std::string status = "Iteration " + std::to_string(iteration) + ": " +
                         "Position (" + std::to_string(x) + ", " + std::to_string(y) + "), " +
                         "Steps: " + std::to_string(steps) + ", " +
                         "Water found: " + std::to_string(waterFound) + ", " +
                         "Status: " + (isInDanger() ? "IN DANGER" : "Safe");

    FileReader::writeToOutput(status);
}
