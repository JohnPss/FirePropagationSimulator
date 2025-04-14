#include "Simulation.hpp"

int main()
{

    MatrixStruct *m = readFile();
    if (m == NULL)
    {
        cerr << "Failed to read input file." << endl;
        return 1;
    }

    ofstream outputFile("output.dat");
    if (!outputFile.is_open())
    {
        cerr << "Failed to open output file." << endl;
        return 1;
    }

    startSimulation(m, outputFile);

    // Liberar a memória e fechar o arquivo
    // TODO: Adicionar código para liberar a memória da matriz
    outputFile.close();

    return 0;
}
