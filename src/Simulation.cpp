#include "Simulation.hpp"

bool processFireSpread(Fire &fire)
{
    bool fireSpread = fire.spreadIteration();

    std::vector<std::string> fireChanges = fire.getChanges();
    for (const std::string &change : fireChanges)
    {
        FileReader::writeToOutput(change);
    }

    return fireSpread;
}

bool handleAnimalInDanger(Animal &animal, int iteration, int &chancesLeft)
{
    if (chancesLeft <= 0)
    {
        animal.recordDeath(iteration);
        return false;
    }

    bool escaped = animal.tryToEscape();
    if (escaped)
    {
        chancesLeft--;
        return true;
    }
    else
    {
        animal.recordDeath(iteration);
        return false;
    }
}

void runSimulation(MatrixStruct *m)
{
    FileReader::openOutputFile();
    int chancesLeft = 1;
    Animal animal(m);
    Fire fire(m);
    bool animalAlive = true;

    for (int i = 0; i < MAX_ITERATIONS; i++)
    {
        int currentIteration = i + 1;

        if (animalAlive)
        {
            animal.moveAnimal();
        }

        bool fireSpread = processFireSpread(fire);

        FileReader::writeToOutput("Iteração " + std::to_string(currentIteration) + ":");
        FileReader::writeToOutput(Util::generateMatrixStateString(m));

        if (!fireSpread)
        {
            FileReader::writeToOutput("Não há mais árvores queimando!");
            break;
        }

        if (animalAlive && animal.isInDanger())
        {
            animalAlive = handleAnimalInDanger(animal, currentIteration, chancesLeft);
        }
    }

    animal.savePathMap();
}