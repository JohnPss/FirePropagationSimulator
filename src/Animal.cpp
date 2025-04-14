#include "Animal.hpp"

// Inicialização do contador estático
int Animal::stayCounter = 0;

Animal::Animal(MatrixStruct *matrix, ofstream &outputFile) : m(matrix), outPutFile(outputFile), waterFound(0), steps(0), deathIteration(-1)
{
    srand(time(NULL));
    findFirstSafePlace();
    pathSequence.emplace_back(x, y);
    animalPath.resize(m->rows, vector<int>(m->columns, 0));

    if (!outPutFile.is_open())
    {
        cerr << "Error: Could not open animal_journey.dat file!" << endl;
    }

    outPutFile << "Animal journey log:" << endl;
    outPutFile << "Starting position: (" << x << ", " << y << ")" << endl;

    recordPosition();
}

Animal::~Animal()
{
    if (outPutFile.is_open())
    {
        outPutFile << endl
                   << "Journey summary:" << endl;
        // Output path
        outPutFile << "Caminho do animal: ";
        for (size_t idx = 0; idx < pathSequence.size(); ++idx)
        {
            if (idx > 0)
                outPutFile << " -> ";
            outPutFile << "(" << pathSequence[idx].first << "," << pathSequence[idx].second << ")";
        }
        outPutFile << endl;
        // ... rest of summary
        outPutFile << "Passos totais: " << steps << endl;
        outPutFile << "Encontrou água: " << waterFound << (waterFound == 1 ? " vez" : " vezes") << endl;
        if (deathIteration > 0)
        {
            outPutFile << "Iteração cercado: " << deathIteration << endl;
            outPutFile << "Animal sobreviveu: Não" << endl;
        }
        else
        {
            outPutFile << "Iteração cercado: N/A" << endl;
            outPutFile << "Animal sobreviveu: Sim" << endl;
        }
    }
}

void Animal::findFirstSafePlace()
{
    bool found = false;

    for (int i = 0; i < m->rows && !found; i++)
    {
        for (int j = 0; j < m->columns && !found; j++)
        {
            if (m->matrix[i][j] == TREE)
            {
                x = i;
                y = j;
                found = true;
                cout << "Safe place (tree) found at (" << x << ", " << y << ")" << endl;
            }
        }
    }

    if (!found)
    {
        for (int i = 0; i < m->rows && !found; i++)
        {
            for (int j = 0; j < m->columns && !found; j++)
            {
                if (m->matrix[i][j] == EMPTY)
                {
                    x = i;
                    y = j;
                    found = true;
                    cout << "Safe place (empty) found at (" << x << ", " << y << ")" << endl;
                }
            }
        }
    }

    if (!found)
    {
        cerr << "Error: Could not find a safe place for the animal!" << endl;
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
    // Se estiver em área vazia, pode ficar até 3 iterações
    if (shouldStayInEmptyArea())
    {
        cout << "Animal stayed in place at empty area (" << x << ", " << y << ")" << endl;
        outPutFile << "Decision: Stayed in empty area" << endl;
        return true;
    }

    resetStayCounter();

    // Encontrar a melhor célula para movimentação
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

    // Se encontrou células candidatas, move para uma delas aleatoriamente
    if (!candidateCells.empty())
    {
        int randomIndex = rand() % candidateCells.size();
        int newX = candidateCells[randomIndex].first;
        int newY = candidateCells[randomIndex].second;

        steps++;
        outPutFile << "Step " << steps << ": Moving to (" << newX << ", " << newY << ")";

        // Verifica se encontrou água
        if (m->matrix[newX][newY] == WATER)
        {
            m->matrix[newX][newY] = EMPTY;
            waterFound++;
            convertWaterToForest(newX, newY);
            outPutFile << " - Found water! Total found: " << waterFound << endl;
        }
        else
        {
            outPutFile << endl;
        }

        x = newX;
        y = newY;
        pathSequence.emplace_back(x, y);
        recordPosition();

        cout << "Animal moved to (" << x << ", " << y << ")" << endl;
        return true;
    }
    else
    {
        cout << "Animal cannot move! Trapped at (" << x << ", " << y << ")" << endl;
        outPutFile << "WARNING: Animal trapped at (" << x << ", " << y << ")" << endl;
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

    outPutFile << "Converting surrounding cells to forest around (" << x << ", " << y << ")" << endl;

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
    outPutFile << "EMERGENCY: Animal in danger! Trying to escape..." << endl;
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
        cout << "Animal path map saved to animal_path_map.dat" << endl;
    }
    else
    {
        cerr << "Error: Could not save animal path map!" << endl;
    }
}

void Animal::recordDeath(int iteration)
{
    deathIteration = iteration;
    outPutFile << "DEATH: Animal died at iteration " << iteration << " at position (" << x << ", " << y << ")" << endl;
}

void Animal::recordStatus(int iteration)
{
    outPutFile << "Iteration " << iteration << ": ";
    outPutFile << "Position (" << x << ", " << y << "), ";
    outPutFile << "Steps: " << steps << ", ";
    outPutFile << "Water found: " << waterFound << ", ";

    // Add information about danger state
    if (isInDanger())
    {
        outPutFile << "Status: IN DANGER";
    }
    else
    {
        outPutFile << "Status: Safe";
    }
    outPutFile << endl;
}