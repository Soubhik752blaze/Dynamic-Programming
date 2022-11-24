/*Question :- Given a chain of Matrices A1, A2, A3, A4...An. Find the min cost of multiplying these matrices.
The min cost is defined here as the min no of scalar multiplications required
If two Matrices A1 (p x q) and A2 (q x s) are to be multiplied,
The total number of multiplications required to multiply A1 and A2 are: p*q*s*/

// As this problem of matrix multiplication solves one big problem ( minimum operations to get A1.A2….An) and the answer varies in the order the subproblems are being solved,
// we can identify this problem of pattern partition DP.

#include <bits/stdc++.h>
using namespace std;

// f(i,j) gives min cost for multiplying the matrices Ai,....Aj.
int recursive(int i, int j, vector<int> arr)
{
    // base case => If i==j, it means its a single matrix and no operation is required to multiply it so we return 0.
    if (i == j)
        return 0;
    // Try all partitions
    // we run a loop from k = i to j - 1 and try out all possible partitions
    int mini = 1e9;
    for (int k = i; k < j; k++)
    {
        // (arr[i - 1] * arr[k] * arr[j]) = cost for multiplying two resultant final matrices
        // for left side partitioning overall cost
        // for right side partitioning overall cost
        int steps = (arr[i - 1] * arr[k] * arr[j]) + recursive(i, k, arr) + recursive(k + 1, j, arr);
        mini = min(mini, steps);
    }

    // return best possible ans
    return mini;
}

int memoization(int i, int j, vector<int> arr, vector<vector<int>> &dp)
{
    // TC -> o(n^3) and SC -> O(n^2) + O(n) for Auxilliary Stack Space
    //  base case => If i==j, it means its a single matrix and no operation is required to multiply it so we return 0.
    if (i == j)
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    // Try all partitions
    // we run a loop from k = i to j - 1 and try out all possible partitions
    int mini = 1e9;
    for (int k = i; k < j; k++)
    {
        // (arr[i - 1] * arr[k] * arr[j]) = cost for multiplying two resultant final matrices
        // for left side partitioning overall cost
        // for right side partitioning overall cost
        int steps = (arr[i - 1] * arr[k] * arr[j]) + memoization(i, k, arr, dp) + memoization(k + 1, j, arr, dp);
        mini = min(mini, steps);
    }

    // return best possible ans
    return dp[i][j] = mini;
}

int tabulation(vector<int> arr, int n)
{
    // vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, INT_MAX)));
    vector<vector<int>> dp(n, vector<int>(n));
    // base case
    for (int i = 0; i < n; i++)
        dp[i][i] = 0;

    // try out all possible scenarios through looping
    for (int i = n - 1; i >= 1; i--)
        for (int j = i + 1; j < n; j++)
        {
            int mini = 1e9;
            for (int k = i; k < j; k++)
            {
                int steps = (arr[i - 1] * arr[k] * arr[j]) + dp[i][k] + dp[k + 1][j];
                mini = min(mini, steps);
            }
            dp[i][j] = mini;
        }
    // return statement
    return dp[1][n - 1];
}

int mcm(vector<int> arr)
{
    int n = arr.size();
    // vector<vector<int>> dp(n, vector<int>(n, -1));
    // int ans = memoization(1, n - 1, arr, dp);
    int ans = tabulation(arr, n);
    return ans;
}
int main()
{
    vector<int> arr = {10, 20, 30, 40, 50};
    cout << "Min no. of Operations needed are :- " << mcm(arr);
}

// TC -> o(n*n*n)
// SC -> o(n*n)