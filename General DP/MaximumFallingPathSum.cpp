/*Question :- We are given an ‘N*M’ matrix.
We need to find the maximum path sum from any cell of the first row to any cell of the last row.

At every cell we can move in three directions: to the bottom cell (↓), to the bottom-right cell(↘), or to the bottom-left cell(↙).
*/
#include <bits/stdc++.h>
using namespace std;

int recursive(int i, int j, int n, vector<vector<int>> maze)
{
    // base case = reaching 0th row
    if (j < 0 || j >= n)
        return INT_MIN;
    if (i == 0)
        return maze[i][j];
    
    // recurring part -> From every step we go either leftup or up or rightup until [0][0],
    // so we find the max cost out of these 3 ways we can go, by adding the value of that cell to the way
    // that way we have max cost up until that cell in grid
    // we do that until the end point and we have our result
    int way1 = recursive(i - 1, j + 1, n, maze);
    int way2 = recursive(i - 1, j, n, maze);
    int way3 = recursive(i - 1, j - 1, n, maze);
    // final return
    return maze[i][j] + max(way1, max(way2, way3));
}

int memoization(int i, int j, int m, vector<vector<int>> &matrix,
                vector<vector<int>> &dp)
{

    // Base Conditions
    if (j < 0 || j >= m)
        return INT_MIN;
    if (i == 0)
        return matrix[0][j];

    if (dp[i][j] != -1)
        return dp[i][j];

    int up = memoization(i - 1, j, m, matrix, dp);
    int leftDiagonal = memoization(i - 1, j - 1, m, matrix, dp);
    int rightDiagonal = memoization(i - 1, j + 1, m, matrix, dp);

    return dp[i][j] = matrix[i][j] + max(up, max(leftDiagonal, rightDiagonal));
}
int tabulation(int m, int n, vector<vector<int>> maze)
{
    //tabulatio = opposite of memoization direction always
    //so here we form bases in 0th row and make our way upto last row
    //when we reach last row, we take the max of all the row elements
    //for calculation, we just take the same concept used in recursive and memoization, and make changes accordingly
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // base condition
            if (i == 0)
            {
                dp[i][j] = maze[i][j];
                continue;
            }

            int left = INT_MIN, right = INT_MIN;
            int up = dp[i - 1][j];

            if (j >= 1)
                left = dp[i-1][j - 1];
            
            if (j < n - 1 )
                right = dp[i-1][j + 1];

            dp[i][j] = maze[i][j] + max(up, max(left,right));
        }
    }
    // final return step calculation i.e taking the max off the last row
    int maxi = dp[m-1][0];
    for(int j = 1; j < n; j++)
        maxi = max(maxi, dp[m-1][j]);
    return maxi;
}

int optimised(int m, int n, vector<vector<int>> maze)
{
    vector<int> prev(n, 0);

    for (int i = 0; i < m; i++)
    {
        vector<int> row(n, 0);
        for (int j = 0; j < n; j++)
        {
            if (i == 0)
            {
                row[j] = maze[i][j];
                continue;
            }
            int left = INT_MIN, right = INT_MIN;
            int up = prev[j];

            if (j >= 1)
                left = prev[j - 1];
            
            if (j < n - 1)
                right = prev[j + 1];

            row[j] = maze[i][j] + max(up, max(left,right));
        }
        prev = row;
    }
    // final return
    int maxi = prev[0];
    for(int j = 1; j < n; j++)
        maxi = max(maxi, prev[j]);
    return maxi;
}

int getMaxPathSum(vector<vector<int>> maze)
{
    // since we dont know for which starting point we will max sum, we take all starting points into consideration 1 by 1
    // then we have the max taken out of all of them -> ans.
    //used for recursive and memoization
    // int n = maze.size();
    // int m = maze[0].size();

    // vector<vector<int>> dp(n, vector<int>(m, -1));

    // int maxi = INT_MIN;

    // for (int j = 0; j < m; j++)
    // {
    //     int ans = memoization(n - 1, j, m, maze, dp);
    //     maxi = max(maxi, ans);
    // }
    int n = maze.size();
    int m = maze[0].size();

    // int maxi = tabulation(n , m, maze);
    int maxi = optimised(n, m, maze);
    return maxi;
}
int main()
{
    vector<vector<int>> maze{{1, 2, 10, 4},
                             {100, 3, 2, 1},
                             {1, 1, 20, 2},
                             {1, 2, 2, 1}};

    cout << getMaxPathSum(maze);
}


// TC -> o(m*n) + o(m) = o(m*n) if using DP
// SC -> o(m*n) or o(n) if using DP
