#include "Simulation.hpp"

void startSimulation(MatrixStruct *m)
{
    int chancesLeft = 1;
    Animal a = Animal(m);
    Fire f = Fire(m);

    for (int i = 0; i < MAX_ITERATIONS; i++)
    {
        cout << "Iteration " << i + 1 << ":" << endl;
        a.moveAnimal();
        bool aux = f.doIt();
        if (!aux)
        {
            cout << "Nore more trees burning!" << endl;
            break;
        }
        if (a.checkSurvival() && chancesLeft == 1)
        {
            cout << "Animal`s dead, second chance!" << endl;
            a.giveSecondChance();
            chancesLeft--;
        }

        cout
            << endl;
    }

    cout << a.waterFind << " " << a.steps << endl;
}