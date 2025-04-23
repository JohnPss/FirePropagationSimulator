#include "Simulation.hpp"

int main()
{

    MatrixStruct *m = readFile();

    startSimulation(m);

    // Liberar a memória e fechar o arquivo
    // TODO: Adicionar código para liberar a memória da matriz

    return 0;
}
