/**
    Input:
    [
        [1,2,3],
        [4,5,6],
        [7,8,9]
    ]

    Output:
    [1,2,3,6,9,8,7,4,5]
 */

#include <vector>

std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix)
{
    std::vector<int> result;
    if (matrix.empty()) return result;

    int top = 0;
    int bottom = matrix.size() - 1;
    int left = 0;
    int right = matrix[0].size() - 1;

    while (top <= bottom && left <= right)
    {
        // left -> right
        for (int i = left; i < right; ++i)
        {
            result.push_back(matrix[top][i]);
        }
        ++top;

        // top -> bottom
        for (int i = top; i < bottom; ++i)
        {
            result.push_back(matrix[i][right]);
        }
        ++top;

        // right -> left
        if (top <= bottom) // only traverse bottom row if bottom row still exists
        {
            for (int i = right; i >= left; --i)
            {
                result.push_back(matrix[bottom][i]);
            }
            --bottom;
        }

        // bottom -> top
        if (left <= right) // only traverse left column if left column still exists
        {
            for (int i = bottom; i >= top; --i)
            {
                result.push_back(matrix[i][left]);
            }
            ++left;
        }

        return result;
    }
}