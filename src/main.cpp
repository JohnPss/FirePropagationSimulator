#include <iostream>
#include "FileReader.hpp"
#include "config.hpp"
#include "Animal.hpp"

int main()
{

    Animal a = Animal();
    a.findFirstSafePlace(readFile());
    a.moveAnimal(readFile());

    // cout << readFile()->rows << endl;
    return 0;
}
