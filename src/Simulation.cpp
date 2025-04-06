#include "Simulation.hpp"

void startSimulation(MatrixStruct *m)
{

    Animal a = Animal(m);
    Fire f = Fire(m);

    for (int i = 0; i < MAX_ITERATIONS; i++)
    {
        // m->printMatrix();

        cout << "Iteration " << i + 1 << ":" << endl;
        a.moveAnimal();
        // f.spreadFire();
        // f.burning();
        f.doIt();
        // m->printMatrix();
        cout << endl;
    }
}