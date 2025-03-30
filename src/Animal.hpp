#pragma once

#include "MatrixStruct.hpp"
#include "iostream"
using namespace std;

class Animal
{
public:
    int x, y;

    void findFirstSafePlace(MatrixStruct *m);
};