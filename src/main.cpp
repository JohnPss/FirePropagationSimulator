#include <iostream>
#include "FileReader.hpp"
#include "config.hpp"
#include "Animal.hpp"

int main()
{

    MatrixStruct *m = readFile();

    Animal a = Animal();
    a.findFirstSafePlace(m);

    for (int i = 0; i < MAX_ITERATIONS; i++)
    {

        a.moveAnimal(m);
    }

    return 0;
}
