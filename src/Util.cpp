#include "Util.hpp"

namespace Util
{
    // Converts a position (pair of integers) to string
    std::string positionToString(const std::pair<int, int> &pos)
    {
        std::stringstream ss;
        ss << pos.first << "," << pos.second;
        return ss.str();
    }

    // Generates a string representation of the matrix
    std::string generateMatrixStateString(const MatrixStruct *m)
    {
        std::stringstream matrixStr;
        for (int row = 0; row < m->rows; row++)
        {
            for (int col = 0; col < m->columns; col++)
            {
                matrixStr << m->matrix[row][col] << " ";
            }
            matrixStr << "\n";
        }
        matrixStr << "\n";
        return matrixStr.str();
    }
}