/*Question :- We are given a Triangular matrix.
We need to find the minimum path sum from the first row to the last row.

At every cell we can move in only two directions: either to the bottom cell (↓) or to the bottom-right cell(↘)*/

#include <bits/stdc++.h>
using namespace std;

int recursive(int i, int j, vector<vector<int>> &triangle, int n)
{
    // base case we take end point as its not fixed here
    if (i == n - 1)
        return triangle[i][j];

    // we can go two direction from a cell.. coordinate wise (i+1, j) and (i + 1, j + 1)
    int down = recursive(i + 1, j, triangle, n);
    int diagonal = recursive(i + 1, j + 1, triangle, n);

    return triangle[i][j] + min(down, diagonal);
}

int memoization(int i, int j, vector<vector<int>> &triangle, int n, vector<vector<int>> &dp)
{
    // base case we take end point as its not fixed here
    if (i == n - 1)
        return triangle[i][j];

    if (dp[i][j] != -1)
        return dp[i][j];

    // we can go two direction from a cell.. coordinate wise (i+1, j) and (i + 1, j + 1)
    int down = memoization(i + 1, j, triangle, n, dp);
    int diagonal = memoization(i + 1, j + 1, triangle, n, dp);

    return dp[i][j] = triangle[i][j] + min(down, diagonal);
}

int tabulation(vector<vector<int>> &triangle, int n)
{
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // in memoization we go from (0,0) to last row -> top-down approach
    // so in tabulation we go from last row to (0,0) -> bottom-up approach
    // so as base case we have last row for dp made ready and then do the 2 for loop calculation
    for (int j = 0; j < n; j++)
        dp[n - 1][j] = triangle[n - 1][j];

    for (int i = n - 2; i >= 0; i--)
        for (int j = i; j >= 0; j--)
        {

            int down = dp[i + 1][j];
            int diagonal = dp[i + 1][j + 1];

            dp[i][j] = triangle[i][j] + min(down, diagonal);
        }

    return dp[0][0];
}

//short for space optimised function
int so(vector<vector<int>> &triangle, int n)
{
    //we only previous row to calculate current row so we need only 1D array to store previous row result
    vector<int> prev(n,0);

    
    for (int j = 0; j < n; j++)
        prev[j] = triangle[n - 1][j];
        
    for (int i = n - 2; i >= 0; i--){
        vector<int> row(n,0);
        for (int j = i; j >= 0; j--)
        {

            int down = prev[j];
            int diagonal = prev[j + 1];

            row[j] = triangle[i][j] + min(down, diagonal);
        }
        prev = row;
    }

    return prev[0];
}

int minimumPathSum(vector<vector<int>> &triangle, int n)
{
    // vector<vector<int>> dp(n, vector<int>(n, -1));
    // int ans = memoization(0, 0, triangle, n, dp);
    int ans = so(triangle, n);
    return ans;
}
int main()
{
    vector<vector<int>> triangle{{1},
                                 {2, 3},
                                 {3, 6, 7},
                                 {8, 9, 6, 10}};

    int n = triangle.size();

    cout << minimumPathSum(triangle, n);
}

//TC -> o(n*n)
//SC -> o(n*n) or o(n)