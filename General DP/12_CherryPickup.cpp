/*Question :- We are given an ‘N*M’ matrix. Every cell of the matrix has some Cherries on it, mat[i][j] gives us the number of Cherries.
 We have two friends ‘Alice’ and ‘Bob’. initially, Alice is standing on the cell(0,0) and Bob is standing on the cell(0, M-1).
 Both of them can move only to the cells below them in these three directions: to the bottom cell (↓), to the bottom-right cell(↘), or to the bottom-left cell(↙).

When Alica and Bob visit a cell, they take all the Cherries from that cell with them.
It can happen that they visit the same cell, in that case, the Cherries need to be considered only once.
They cannot go out of the boundary of the given matrix, we need to return the maximum number of Cherries that Bob and Alice can together collect.*/

//[3D DP]
//[Hardest problem till so far on grid DP]
#include <bits/stdc++.h>
using namespace std;

int recursive(int i, int j1, int j2, int m, int n, vector<vector<int>> grid)
{
    // fixed starting point and variable ending point
    //  base cases are written below
    // "i" will be same for both as for every step, both person go to a cell in lower row
    //  "i" or row number will be same for both person so we can keep them as common i... j1 and j2 are column numbers for alice and bob
    if (j1 < 0 || j2 < 0 || j1 > n - 1 || j2 > n - 1)
        return -1e9;

    if (i == m - 1)
    {
        // if bob and alice final destination is same, consider cell value only once...
        if (j1 == j2)
            return grid[i][j1];
        else
            return grid[i][j1] + grid[i][j2];
    }

    // Write all possible traversal ways and take max of ways for both person
    // for every specific step of alice, bob has 3 directions to go
    // so total 9 states of progression are there in this case..
    // we reenact the scenario here using dj1 and dj2 variables
    // for every traversal to lower row, we see which state is yielding max cherries for alice and bob combined
    // we pick that state and move ahead
    int maxi = -1e8;
    for (int dj1 = -1; dj1 <= 1; dj1++){
        for (int dj2 = -1; dj2 <= 1; dj2++){
            int ans = 0;
            // if bob and alice final destination is same, consider cell value only once...
            if (j1 == j2)
                ans = grid[i][j1] + recursive(i + 1, j1 + dj1, j2 + dj2, m, n, grid);
            else
                ans = grid[i][j1] + grid[i][j2] + recursive(i + 1, j1 + dj1, j2 + dj2, m, n, grid);
            maxi = max(maxi, ans);
        }
    }

    // final return
    return maxi;
}

int memoization(int i, int j1, int j2, int m, int n, vector<vector<int>> grid, vector<vector<vector<int>>> &dp)
{
    // j1 is position of alice and j2 of bob
    if (j1 < 0 || j2 < 0 || j1 > n - 1 || j2 > n - 1)
        return -1e9;

    if (i == m - 1){
        // if bob and alice final destination is same, consider cell value only once...
        if (j1 == j2)
            return grid[i][j1];
        else
            return grid[i][j1] + grid[i][j2];
    }

    if (dp[i][j1][j2] != -1)
        return dp[i][j1][j2];

    int maxi = -1e8;
    for (int dj1 = -1; dj1 <= 1; dj1++) {
        for (int dj2 = -1; dj2 <= 1; dj2++){
            int ans = 0;
            // if bob and alice final destination is same, consider cell value only once...
            if (j1 == j2)
                ans = grid[i][j1] + memoization(i + 1, j1 + dj1, j2 + dj2, m, n, grid, dp);
            else
                ans = grid[i][j1] + grid[i][j2] + memoization(i + 1, j1 + dj1, j2 + dj2, m, n, grid, dp);
            maxi = max(maxi, ans);
        }
    }

    // final return
    return dp[i][j1][j2] = maxi;
}

int tabulation(int m, int n, vector<vector<int>> grid)
{
    /*For the tabulation approach, it is better to understand what a cell in the 3D DP array means. As we had done in memoization, we will initialize a dp[] array of size [N][M][M].

    So now, when we say dp[2][0][3], what does it mean? It means that we are getting the value of maximum chocolates collected by Alice and Bob, when Alice is at (2,0) and Bob is at (2,3).*/
    // so, j1 is alice's position and j2 is bob's position
    // tabulation = opposite of memoization direction always
    // so here we form bases in 0th row and make our way upto last row
    // for calculation, we just take the same concept used in recursive and memoization, and make modification accordingly
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(n, 0)));
    // forming base case
    for (int j1 = 0; j1 < n; j1++)
        for (int j2 = 0; j2 < n; j2++){
            if (j1 == j2)
                dp[m - 1][j1][j2] = grid[m - 1][j1];
            else
                dp[m - 1][j1][j2] = grid[m - 1][j1] + grid[m - 1][j2];
        }
    // express every step in for loop
    for (int i = m - 2; i >= 0; i--){
        for (int j1 = 0; j1 < n; j1++){
            for (int j2 = 0; j2 < n; j2++)
            {
                int maxi = -1e8;
                for (int dj1 = -1; dj1 <= 1; dj1++){
                    for (int dj2 = -1; dj2 <= 1; dj2++){
                        int value;
                        // if bob and alice final destination is same, consider cell value only once...
                        if (j1 == j2)
                            value = grid[i][j1];
                        else
                            value = grid[i][j1] + grid[i][j2];

                        //if next steps are valid take it, else make it invalid
                        if (j2 + dj2 >= 0 && j1 + dj1 >= 0 && j1 + dj1 <= n - 1 && j2 + dj2 <= n - 1)
                            value += dp[i + 1][j1 + dj1][j2 + dj2];
                        else
                            value += -1e9;
                        maxi = max(maxi, value);
                    }
                }
                dp[i][j1][j2] = maxi;
            }
        }
    }

    return dp[0][0][n - 1];
}

int optimised(int m, int n, vector<vector<int>> grid)
{
    // same as tabulation but we are reducing the space taken by taking only a 2D matrix
    vector<vector<int>> prev(n, vector<int>(n, 0)), temp(n, vector<int>(n, 0));
    ;
    // forming base case
    for (int j1 = 0; j1 < n; j1++)
        for (int j2 = 0; j2 < n; j2++)
        {
            if (j1 == j2)
                prev[j1][j2] = grid[m - 1][j1];
            else
                prev[j1][j2] = grid[m - 1][j1] + grid[m - 1][j2];
        }
    // express every step in for loop
    for (int i = m - 2; i >= 0; i--)
    {
        for (int j1 = 0; j1 < n; j1++)
        {
            for (int j2 = 0; j2 < n; j2++)
            {
                int maxi = -1e8;
                for (int dj1 = -1; dj1 <= 1; dj1++)
                {
                    for (int dj2 = -1; dj2 <= 1; dj2++)
                    {
                        int ans;
                        // if bob and alice final destination is same, consider cell value only once...
                        if (j1 == j2)
                            ans = grid[i][j1];
                        else
                            ans = grid[i][j1] + grid[i][j2];
                        if (j2 + dj2 >= 0 && j1 + dj1 >= 0 && j1 + dj1 <= n - 1 && j2 + dj2 <= n - 1)
                            ans += prev[j1 + dj1][j2 + dj2];
                        else
                            ans += -1e9;
                        maxi = max(maxi, ans);
                    }
                }
                temp[j1][j2] = maxi;
            }
        }
        prev = temp;
    }

    return prev[0][n - 1];
}

int getmaxcherry(vector<vector<int>> grid)
{
    // function for recursion and memoization
    //  int m = grid.size();
    //  int n = grid[0].size();
    //  vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(n, -1)));

    // int maxi = memoization(0, 0, n - 1, m, n, grid, dp);
    int m = grid.size();
    int n = grid[0].size();
    int maxi = optimised(m, n, grid);
    return maxi;
}
int main()
{
    vector<vector<int>> grid{{2, 3, 1, 2},
                             {3, 4, 2, 2},
                             {5, 6, 3, 5}};

    cout << getmaxcherry(grid);
}

// TC -> O(N*M*M)*9
// Reason: The outer nested loops run for (N*M*M) times and the inner two nested loops run for 9 times.
// SC -> O(N*M*M) or o(M*M) if using optimisation of space
