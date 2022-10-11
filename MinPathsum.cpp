/*Question :-Given a m x n grid filled with non-negative numbers, 
find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.*/


#include <bits/stdc++.h>
using namespace std;

int countwaysrecurive(int i, int j, vector<vector<int>> maze)
{
    // base cases
    if (i == 0 && j == 0)
        return maze[i][j];
    if (i < 0 || j < 0)
        return INT_MAX;
    // recurring part -> From every step we go either left or up until [0][0],
    // so we count the total no of ways we can go by adding recursively
    int way1 = countwaysrecurive(i - 1, j, maze);
    int way2 = countwaysrecurive(i, j - 1, maze);
    // final return
    return maze[i][j] + min(way1,way2);
}

int countwaysmemoization(int i, int j, vector<vector<int>> &maze, vector<vector<int>> &dp)
{
    
    // base cases
    if (i == 0 && j == 0)
        return maze[i][j];
    if (i < 0 || j < 0)
        return INT_MAX;

    // use of dp table to remember results
    if (dp[i][j] != -1)
        return dp[i][j];    
    // recurring part
    int way1 = countwaysmemoization(i - 1, j, maze, dp); // dp[i - 1][j];
    int way2 = countwaysmemoization(i, j - 1, maze, dp); // dp[i][j + 1];
    // final return
    return dp[i][j] = maze[i][j] + min(way1,way2);
}
int countwaystabulation(int m, int n, vector<vector<int>> maze)
{
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++)
        {
            // base condition
            if (i == 0 && j == 0)
            {
                dp[i][j] = maze[i][j];
                continue;
            }
            
            int up = 0, left = 0;
            if (i > 0)
                up = dp[i - 1][j];
            else
                up = INT_MAX;

            if (j > 0)
                left = dp[i][j - 1];
            else
                left = INT_MAX;
            dp[i][j] = maze[i][j] + min(up,left);
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
            if (i == 0 && j == 0)
            {
                row[j] = maze[i][j];
                continue;
            }
            int up = 0, left = 0;
            if (i > 0)
                up = prev[j];
            else
                up = INT_MAX;

            if (j > 0)
                left = row[j - 1];
            else
                left = INT_MAX;

            row[j] = maze[i][j] + min(up, left);
        }
        prev = row;
    }
    // final return
    return prev[n - 1];
}

int mazeObstacles(int m, int n, vector<vector<int>> maze)
{
    // int ans = countwaysrecurive(m - 1 , n - 1 , maze);
    // vector<vector<int>> dp(m, vector<int>(n, -1));
    // int ans = countwaysmemoization(m - 1, n - 1, maze, dp);
    //int ans = countwaystabulation(m, n, maze);
    int ans = countwaysoptimised(m, n, maze);

    return ans;
}
int main()
{
    vector<vector<int>> maze{{5,9,6},
                             {11,9,2}};

    int m = maze.size();
    int n = maze[0].size();

    cout << mazeObstacles(m, n, maze);
}

// TC -> o(m*n) if using DP
// SC -> o(m*n) or o(n) if using DP
