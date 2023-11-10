/*Question :- We are given an array ‘ARR’ of size ‘N’ and a number ‘Target’.
Our task is to build an expression from the given array where we can place a ‘+’ or ‘-’ sign in front of an integer.
We want to place a sign in front of every integer of the array and get our required target.
We need to count the number of ways in which we can achieve our required target.
Please note integers might have zeroes as elements*/

#include <bits/stdc++.h>
using namespace std;

int findTargetSumWays(vector<int> &A, int target)
{
    int S = target;
    int sum = 0;
    int n = A.size();
    for (int i = 0; i < n; i++)
        sum += A[i];
    if (S > sum || (sum - S) % 2 != 0)
        return 0;

    vector<vector<int>> dp(n + 1, vector<int> ((sum - S/ 2) + 1, 0));

    int countZeroes = 0;
    for (int i = 0; i < n; i++)
        if (A[i] == 0)
            countZeroes++;

    for (int i = 0; i < n + 1; i++)
        dp[i][0] = 1;
    if(A[0] <= target)
        dp[0][A[0]] = 1;

    for (int i = 1; i < n + 1; i++)
        for (int j = 1; j < ((sum - S) / 2) + 1; j++)
        {
            if (A[i - 1] == 0)
                dp[i][j] = dp[i - 1][j];
            else if (A[i - 1] <= j)
                dp[i][j] = dp[i - 1][j - A[i - 1]] + dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j];
        }

    return pow(2, countZeroes) * dp[n][(sum - S) / 2];
}

int main()
{
    vector<int> arr = {1, 2, 2, 4};
    int target = 1;

    int n = arr.size();
    cout << "The number of ways found is " << findTargetSumWays(arr, target);
}
