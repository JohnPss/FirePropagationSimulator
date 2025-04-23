#include "Simulation.hpp"
#include <sstream>

void startSimulation(MatrixStruct *m)
{
    FileReader::openOutputFile();
    int chancesLeft = 1; // Number of chances for the animal
    Animal a(m);         // Create an animal
    Fire f(m);           // Create fire

    auto positionToString = [](const std::pair<int, int> &pos) -> std::string
    {
        std::stringstream ss;
        ss << pos.first << "," << pos.second;
        return ss.str();
    };

    for (int i = 0; i < MAX_ITERATIONS; i++)
    {
        a.recordStatus(i + 1);
        a.moveAnimal();

        bool fireSpread = f.doIt();
        // Get fire changes and write to output
        vector<string> fireChanges = f.getChangeLog();
        for (const string &change : fireChanges)
        {
            FileReader::writeToOutput(change);
        }

        // Print matrix state
        FileReader::writeToOutput("Iteração " + std::to_string(i + 1) + ":");

        std::stringstream matrixStr;
        for (int row = 0; row < m->rows; row++)
        {
            for (int col = 0; col < m->columns; col++)
            {
                matrixStr << m->matrix[row][col] << " ";
            }
            matrixStr << "\n";
        }
        matrixStr << "\n";
        FileReader::writeToOutput(matrixStr.str());

        if (!fireSpread)
        {
            FileReader::writeToOutput("No more trees burning!");
            break;
        }

        // Check if animal is in danger
        if (a.isInDanger())
        {
            if (chancesLeft > 0)
            {

                FileReader::writeToOutput("Animal is in danger, trying to escape!");

                bool escaped = a.tryToEscape();
                if (escaped)
                {
                    FileReader::writeToOutput("New Animal Position: " + positionToString(a.getPosition()));
                    chancesLeft--;
                }
                else
                {
                    // Animal couldn't escape
                    a.recordDeath(i + 1);
                    FileReader::writeToOutput("Animal failed to escape and died at iteration " + std::to_string(i + 1));

                    chancesLeft = 0; // No more chances
                }
            }
            else
            {
                // Animal has no more chances
                a.recordDeath(i + 1);
                FileReader::writeToOutput("Animal died at iteration " + std::to_string(i + 1) + " with no chances left");
                // Simulation continues even after animal's death
            }
        }
    }

    // Save the animal's path and close the output file
    a.savePathMap();
}