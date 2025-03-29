#include <iostream>
#include "FileReader.hpp"
int main()
{
    FileReader reader = FileReader();

    cout << reader.readFile()->rows << endl;

    return 0;
}
