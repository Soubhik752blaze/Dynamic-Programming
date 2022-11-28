/*Question :- Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.*/

#include <bits/stdc++.h>
using namespace std;
// VIDEO EXPLANATION :- https://www.youtube.com/watch?v=auS1fynpnjo&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=57s
//  better to go with tabulation when it comes to square DP problems because that is intuitive
int submatriceswithall1s(vector<vector<int>> matrix)
{
    int row = matrix.size();
    int col = matrix[0].size();
    // creating a exact similar structure matrix called dp
    // dp[i][j] tells us how many squares whose right bottom end at (i,j)
    vector<vector<int>> dp(row, vector<int>(col, 0));
    // all row = 0 and col = 0 cells can be at max only 1 sized squsares ending at those cells itself it they are themselves having cell value 1.
    for (int r = 0; r < row; r++)
        dp[r][0] = matrix[r][0];

    for (int c = 0; c < col; c++)
        dp[0][c] = matrix[0][c];

    // for all other cells, they can be min 1 sized square if they are containing 1.
    // if the cell is not containing 1, the no of squares are 0 by default.
    // for them to have ith sized squares, the min of the values at cells dp[i-1][j-1] ,dp[i-1][j] and dp[i][j-1] should be i
    // thus, we store the max no of squares possible at (i,j)th dp cell using this formula and use this cell value to find the answer for the next cells further down the row and columns
    for (int r = 1; r < row; r++)
        for (int c = 1; c < col; c++)
        {
            if (matrix[r][c] == 1)
                dp[r][c] = 1 + min(dp[r - 1][c], min(dp[r - 1][c - 1], dp[r][c - 1]));
        }
    // find total no of squares
    int ans = 0;
    for (int r = 0; r < row; r++)
        for (int c = 0; c < col; c++)
            ans += dp[r][c];

    return ans;
}
int main()
{
    vector<vector<int>> matrix = {{0, 1, 1, 1},
                                  {1, 1, 1, 1},
                                  {0, 1, 1, 1}};
    cout << "No of square submatrices have all 1s are " << submatriceswithall1s(matrix);
}

// TC -> O(n*m)
// SC -> O(n*m)