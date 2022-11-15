/*Coin Change Problem Minimum Numbers of coins
We are given a target sum of ‘X’ and ‘N’ distinct numbers denoting the coin denominations.
We need to tell the minimum number of coins required to reach the target sum.
We can pick a coin denomination for any number of times we want.*/
#include <bits/stdc++.h>
using namespace std;

// same as subsetsum with target problem, we can pick or not pick a element
// but here for every coin, supply is infinite
// So, when we take a coin, we donot move the further down index and keep taking it until the target gets smaller than the coin value
// Then, since we need min no of coins, we take min of take and not_Take solutions
int recursive(int i, vector<int> &arr, int target)
{
    // base case
    if (i == 0)
    {
        if (target % arr[0] == 0)
            return target / arr[0];
        else
            return 1e9;
    }

    // explore all posibilites
    int not_taken = recursive(i - 1, arr, target);
    int taken = 1e9;
    if (arr[i] <= target)
    {
        taken = 1 + recursive(i, arr, target - arr[i]);
    }
    // return minimum
    return min(taken, not_taken);
}

int memoization(int i, int target, vector<int> &arr, vector<vector<int>> &dp)
{
    // base case
    if (i == 0)
    {
        if (target % arr[0] == 0)
            return target / arr[0];
        else
            return 1e9;
    }

    if (dp[i][target] != -1)
        return dp[i][target];

    // explore all posibilites
    int not_taken = memoization(i - 1, target, arr, dp);
    int taken = 1e9;
    if (arr[i] <= target)
    {
        taken = 1 + memoization(i, target - arr[i], arr, dp);
    }
    return min(taken, not_taken);
}

int tabulation(int k, vector<int> &arr)
{
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));
    // base case creation for tabulation
    for (int i = 0; i <= k; i++)
    {
        if (i % arr[0] == 0)
            dp[0][i] = i / arr[0];
        else
            dp[0][i] = 1e9;
    }
    //for loop and same recurrence 
    for (int i = 1; i < n; i++)
        for (int target = 0; target <= k; target++)
        {
            int not_taken = dp[i - 1][target];
            int taken = 1e9;
            if (arr[i] <= target)
                taken = 1 + dp[i][target - arr[i]];
            dp[i][target] = min(taken, not_taken);
        }
    //return statement
    return dp[n - 1][k];
}


int spaceoptimised(int k, vector<int> &arr)
{
    int n = arr.size();
    vector<int> prev(k + 1, 0), curr(k+1, 0);
    // base case creation for tabulation
    for (int i = 0; i <= k; i++)
    {
        if (i % arr[0] == 0)
            prev[i] = i / arr[0];
        else
            prev[i] = 1e9;
    }
    //for loop and same recurrence 
    for (int i = 1; i < n; i++){
        for (int target = 0; target <= k; target++)
        {
            int not_taken = prev[target];
            int taken = 1e9;
            if (arr[i] <= target)
                taken = 1 + curr[target - arr[i]];
            curr[target] = min(taken, not_taken);
        }
        prev = curr;
    }
    //return statement
    return prev[k];
}

int minimumcoins(vector<int> &arr, int target)
{
    int n = arr.size();
    // vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    // int ans = memoization(n - 1, target, arr, dp);
    int ans = spaceoptimised(target, arr);
    if (ans >= 1e9)
        return -1;
    return ans;
}
int main()
{
    vector<int> arr = {9, 7, 6, 1};
    int target = 13;

    cout << "The minimum number of coins required to form the target sum is " << minimumcoins(arr, target);
    return 0;
}