/*Question:-Given two values M and N, which represent a matrix[M][N].
We need to find the total unique paths from the top-left cell (matrix[0][0]) to the rightmost cell (matrix[M-1][N-1]).
A cell with -1 value means it is a blocked cell (cant travel through it) and 0 means it is allowed to travel
At any cell we are allowed to move in only two directions:- bottom and right.
*/

#include <bits/stdc++.h>
using namespace std;

int countwaysrecurive(int i, int j, vector<vector<int>> maze)
{
    // base cases
    if (i == 0 && j == 0)
        return 1;
    if (i < 0 || j < 0 || maze[i][j] == -1)
        return 0;
    // recurring part -> From every step we go either left or up until [0][0],
    // so we count the total no of ways we can go by adding recursively
    int way1 = countwaysrecurive(i - 1, j, maze);
    int way2 = countwaysrecurive(i, j - 1, maze);
    // final return
    return way1 + way2;
}

int countwaysmemoization(int i, int j, vector<vector<int>> maze, vector<vector<int>> &dp)
{

    // base cases
    if (i > 0 && j > 0 && maze[i][j] == -1)
        return 0;
    if (i == 0 && j == 0)
        return 1;
    if (i < 0 || j < 0)
        return 0;

    // use of dp table to remember results
    if (dp[i][j] != -1)
        return dp[i][j];
    // recurring part
    int way1 = countwaysmemoization(i - 1, j, maze, dp); // dp[i - 1][j];
    int way2 = countwaysmemoization(i, j - 1, maze, dp); // dp[i][j + 1];
    // final return
    return dp[i][j] = way1 + way2;
}
int countwaystabulation(int m, int n, vector<vector<int>> maze)
{
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // base condition
            if (maze[i][j] == -1)
            {
                dp[i][j] = 0;
                continue;
            }
            if (i == 0 && j == 0)
            {
                dp[i][j] = 1;
                continue;
            }

            int up = 0, left = 0;
            if (i > 0)
                up = dp[i - 1][j];
            if (j > 0)
                left = dp[i][j - 1];
            dp[i][j] = up + left;
        }
    }
    // final return
    return dp[m - 1][n - 1];
}

int countwaysoptimised(int m, int n, vector<vector<int>> maze)
{
    vector<int> prev(n, 0);

    for (int i = 0; i < m; i++)
    {
        vector<int> row(n, 0);
        for (int j = 0; j < n; j++)
        {
            if (maze[i][j] == -1)
            {
                row[j] = 0;
                continue;
            }
            if (i == 0 || j == 0)
            {
                row[j] = 1;
                continue;
            }
            int up = 0, left = 0;
            if (i > 0)
                up = prev[j];
            if (j > 0)
                left = row[j - 1];
            row[j] = up + left;
        }
        prev = row;
    }
    // final return
    return prev[n - 1];
}

int mazeObstacles(int m, int n, vector<vector<int>> maze)
{
    //  int ans = countwaysrecurive(m - 1 , n - 1 , maze);
    // vector<vector<int>> dp(m, vector<int>(n, -1));
    // int ans = countwaysmemoization(m - 1, n - 1, maze, dp);
    int ans = countwaystabulation(m, n, maze);
    // int ans = countwaysoptimised(m, n, maze);

    return ans;
}
int main()
{
    vector<vector<int>> maze{{0, 0, 0},
                             {0, -1, 0},
                             {0, 0, 0}};

    int m = maze.size();
    int n = maze[0].size();

    cout << mazeObstacles(m, n, maze);
}

// TC -> o(m*n) if using DP
// SC -> o(m*n) or o(n) if using DP
