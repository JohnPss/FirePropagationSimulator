#include "Simulation.hpp"

bool processFireSpread(Fire &fire)
{
    // Método renomeado: doIt() -> spreadIteration()
    bool fireSpread = fire.spreadIteration();

    // Método renomeado: getChangeLog() -> getChanges()
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
        FileReader::writeToOutput("Animal morreu na iteração " +
                                  std::to_string(iteration) + " sem chances restantes");
        return false;
    }

    FileReader::writeToOutput("Animal está em perigo, tentando escapar!");

    bool escaped = animal.tryToEscape();
    if (escaped)
    {
        FileReader::writeToOutput("Nova Posição do Animal: " +
                                  Util::positionToString(animal.getPosition()));
        chancesLeft--;
        return true;
    }
    else
    {
        animal.recordDeath(iteration);
        FileReader::writeToOutput("Animal não conseguiu escapar e morreu na iteração " +
                                  std::to_string(iteration));
        return false;
    }
}

void startSimulation(MatrixStruct *m)
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
            animal.recordStatus(currentIteration);
            animal.moveAnimal();
        }

        bool fireSpread = processFireSpread(fire);

        FileReader::writeToOutput("Iteração " + std::to_string(currentIteration) + ":");
        FileReader::writeToOutput(Util::generateMatrixStateString(m));

        // Lógica de término mantida
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
    // FileReader::closeOutputFile(); // Adicionado para fechar arquivo
}