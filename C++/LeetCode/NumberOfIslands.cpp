// Count islands in grid (connected 1's)

// Approach: DFS
// - Loop grid
// - When we hit 1, DFS or BFS to mark visited, then increment count

#include <vector>

void dfs(std::vector<std::vector<int>>& grid, int i, int j)
{
    int m = grid.size(); // total rows
    int n = grid[0].size(); // total columns

    // base case: stop if out of bounds or 0 (water)
    if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == 0)
        return;
        
    grid[i][j] = 0; // mark current land cell as visited

    dfs(grid, i+1, j); // down
    dfs(grid, i-1, j); // up
    dfs(grid, i, j+1); // right
    dfs(grid, i, j-1); // left
}

int numIslands(std::vector<std::vector<int>>& grid)
{
    int count = 0;

    // traverse grid
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            // when we hit 1, it's a new island
            if (grid[i][j] == 1)
            {
                // flood fill entire island by marking all connected land
                dfs(grid, i, j);

                // increase island count after fully exploring it
                ++count;
            }
        }
    }

    return count;
}