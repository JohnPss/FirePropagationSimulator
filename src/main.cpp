#include "Simulation.hpp"

int main()
{
    MatrixStruct *m = readFile();
    runSimulation(m);
    return 0;
}
