#include "Simulation.hpp"

int main()
{

    MatrixStruct *m = readFile();

    // startSimulation(m);
    // Fire fire = Fire(m);

    startSimulation(m);

    // for (int i = 0; i < 20; i++)
    // {
    //     cout << "Iteração " << i << ":" << endl;
    //     fire.spreadFire();
    //     fire.burning();
    //     m->printMatrix();
    //     cout << endl;
    // }

    return 0;
}
