#include "Simulation.hpp"
#include <sstream>

void startSimulation(MatrixStruct *m, ofstream &outputFile)
{
    int chancesLeft = 1;     // Number of chances for the animal
    Animal a(m, outputFile); // Create an animal
    Fire f(m);               // Create fire

    // ofstream outputFile(outputPath);
    // if (!outputFile.is_open())
    // {
    //     cerr << "Error: Unable to open output file: " << outputPath << endl;
    //     return;
    // }

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
            outputFile << change << endl;
        }

        // Print matrix state
        outputFile << "Iteração " << (i + 1) << ":" << endl;
        for (int row = 0; row < m->rows; row++)
        {
            for (int col = 0; col < m->columns; col++)
            {
                outputFile << m->matrix[row][col] << " ";
            }
            outputFile << endl;
        }
        outputFile << endl;

        if (!fireSpread)
        {
            cout << "No more trees burning!" << endl;
            outputFile << "No more trees burning!" << endl;
            break;
        }

        // Check if animal is in danger
        if (a.isInDanger())
        {
            if (chancesLeft > 0)
            {
                cout << "Animal is in danger, trying to escape!" << endl;
                outputFile << "Animal is in danger, trying to escape!" << endl;

                bool escaped = a.tryToEscape();
                if (escaped)
                {
                    outputFile << "New Animal Position: " << positionToString(a.getPosition()) << endl;
                    chancesLeft--;
                }
                else
                {
                    // Animal couldn't escape
                    a.recordDeath(i + 1);
                    outputFile << "Animal failed to escape and died at iteration " << (i + 1) << endl;
                    chancesLeft = 0; // No more chances
                }
            }
            else
            {
                // Animal has no more chances
                a.recordDeath(i + 1);
                outputFile << "Animal died at iteration " << (i + 1) << " with no chances left" << endl;
                // Simulation continues even after animal's death
            }
        }

        cout << endl;
    }

    // Save the animal's path and close the output file
    a.savePathMap();
}