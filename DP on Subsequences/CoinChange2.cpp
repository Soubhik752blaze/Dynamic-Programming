/*Coin Change Problem
We are given an array Arr with N distinct coins and a target. 
We have an infinite supply of each coin denomination. 
We need to find the number of ways we sum up the coin values to give us the target.

Each coin can be used any number of times.*/
#include<bits/stdc++.h>
using namespace std;

// same as minimum coins problem
// only difference here is we need to count the no of ways we can arrange coins
// so accordingly we change our base case to return 1 for every valid way and 0 for not valid ways
// for return statement, we add the ways instead of taking minimum
int recursive(int i, int target, vector<int> &arr){
    //base case
    //target == 0 use case not included as traversing more elements might give more results
    if (i == 0)
        {
            if (target % arr[0] == 0)
                return 1;
            else
                return 0;
        }
    
    // explore all possibilites
    int not_take = recursive(i - 1, target, arr);
    int take = 0;
    if (arr[i] <= target)
        take = recursive(i, target - arr[i], arr);
    // return all ways
    return take + not_take;
}
int memoization(int i, int target, vector<int> &arr, vector<vector<int>> &dp)
    {
        // basecase
        if (i == 0)
        {
            if (target % arr[0] == 0)
                return 1;
            else
                return 0;
        }
        if(dp[i][target] != -1)
            return dp[i][target];
        // explore all possibilites
        int not_take = memoization(i - 1, target, arr, dp);
        int take = 0;
        if (arr[i] <= target)
            take = memoization(i, target - arr[i], arr, dp);
        // return all ways
        return dp[i][target] = take + not_take;
    }
int tabulation(int k, vector<int> arr)
{
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));
    // base case creation for tabulation
    for (int i = 0; i <= k; i++)
    {
        if (i % arr[0] == 0)
            dp[0][i] = 1;
        else
            dp[0][i] = 0;
    }
    //for loop and same recurrence 
    for (int i = 1; i < n; i++)
        for (int target = 0; target <= k; target++)
        {
            int not_taken = dp[i - 1][target];
            int taken = 0;
            if (arr[i] <= target)
                taken = 1 + dp[i][target - arr[i]];
            dp[i][target] = min(taken, not_taken);
        }
    //return statement
    return dp[n - 1][k];
}
int spaceoptimised(int k, vector<int> arr)
{
    int n = arr.size();
    vector<int> curr(k + 1, 0), prev(k+1, 0);
    // base case creation for tabulation
    for (int i = 0; i <= k; i++)
    {
        if (i % arr[0] == 0)
            prev[i] = 1;
        else
            prev[i] = 0;
    }
    //for loop and same recurrence 
    for (int i = 1; i < n; i++){
        for (int target = 0; target <= k; target++)
        {
            int not_taken = prev[target];
            int taken = 0;
            if (arr[i] <= target)
                taken = 1 + curr[target - arr[i]];
            curr[target] = min(taken, not_taken);
        }
        prev = curr;
    }
    //return statement
    return prev[k];
}

int countWaysToMakeChange(int amount, vector<int> &coins)
    {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int> (amount + 1, -1));
        return memoization(n - 1, amount, coins, dp);
    }
int main()
{
  vector<int> arr ={1,2,5};
  int target=5;
                                 
  cout<<"The total number of ways is " <<countWaysToMakeChange(target, arr);
}

//TC -> o(n*target)
//SC -> o(target)