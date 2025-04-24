#pragma once

#include "MatrixStruct.hpp"
#include <string>
#include <utility>
#include <sstream>
#include <vector>

namespace Util
{
    std::string positionToString(const std::pair<int, int> &pos);
    std::string generateMatrixStateString(const MatrixStruct *m);
}
