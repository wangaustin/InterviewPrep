// If a cell is 0 -> set entire row & column to 0

// Approach
// - O(1) space
// - First row + first column as markers

#include <vector>

void setZeroes(std::vector<std::vector<int>>& matrix)
{
    int m = matrix.size(); // number of rows
    int n = matrix[0].size(); // number of columns

    // track whether the FIRST row/column need to be zeroed
    bool firstRowZero = false;
    bool firstColZero = false;

    // check if first column has any zero
    for (int i = 0; i < m; ++i)
        if (matrix[i][0] == 0) firstColZero = true;
    
    // check if first row has any zero
    for (int j = 0; j < n; ++j)
        if (matrix[0][j]) firstRowZero = true;

    // use first row & column as markers
    // i.e. if matrix[i][j] is 0, mark row i and column j
    for (int i = 1; i < m; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            if (matrix[i][j] == 0)
            {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    // zero the cells based on markers
    for (int i = 1; i < m; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            if (matrix[i][0] == 0 || matrix[0][j] == 0)
            {
                matrix[i][j] = 0;
            }
        }
    }

    // handle first row separately
    if (firstRowZero)
    {
        for (int j = 0; j < n; ++j)
            matrix[0][j] = 0;
    }

    if (firstColZero)
    {
        for (int i = 0; i < m; ++i)
            matrix[i][0] = 0;
    }
}