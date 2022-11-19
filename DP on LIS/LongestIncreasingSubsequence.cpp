/*Question :- Given an integer array nums, return the length of the longest strictly increasing subsequence.*/

#include <bits/stdc++.h>
using namespace std;
int recursive(int i, vector<int> nums, int prev_ind, int n)
{
    // base case
    if (i == n)
        return 0;

    // explore all approach and return best fit option
    // not part of LIS
    int not_take = recursive(i + 1, nums, prev_ind, n);
    int take = 0;
    // part of LIS
    if (prev_ind == -1 || nums[i] > nums[prev_ind])
    {
        take = 1 + recursive(i + 1, nums, i, n);
    }

    return max(take, not_take);
}
int memoization(int i, vector<int> nums, int prev_ind, int n, vector<vector<int>> &dp)
{
    // base case
    if (i == n)
        return 0;
    //since we cant array[-1] so we coordinate shift and store every prev_ind as prev_ind+1 while storing to dp 
    if (dp[i][prev_ind + 1] != -1)
        return dp[i][prev_ind + 1];
    // explore all approach and return best fit option
    // not part of LIS
    int not_take = memoization(i + 1, nums, prev_ind, n, dp);
    int take = 0;
    // part of LIS
    if (prev_ind == -1 || nums[i] > nums[prev_ind])
    {
        take = 1 + memoization(i + 1, nums, i, n, dp);
    }

    return dp[i][prev_ind + 1] = max(take, not_take);
}

int tabulation(vector<int> nums)
{
    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    // base case already taken care
    // general scenario
    for (int i = n - 1; i >= 0; i--)
        for (int prev_ind = i - 1; prev_ind >= -1; prev_ind--)
        {
            int not_take = dp[i + 1][prev_ind + 1];
            int take = 0;
            // part of LIS
            if (prev_ind == -1 || nums[i] > nums[prev_ind])
            {
                take = 1 + dp[i + 1][i + 1];
            }

            dp[i][prev_ind + 1] = max(take, not_take);
        }

    return dp[0][-1 + 1];
    // return statement
}

int spaceoptimisation(vector<int> nums)
{
    int n = nums.size();
    vector<int> next(n + 1, 0), curr(n + 1, 0);
    // base case already taken care
    // general scenario
    for (int i = n - 1; i >= 0; i--){
        for (int prev_ind = i - 1; prev_ind >= -1; prev_ind--)
        {
            int not_take = next[prev_ind + 1];
            int take = 0;
            // part of LIS
            if (prev_ind == -1 || nums[i] > nums[prev_ind])
            {
                take = 1 + next[i + 1];
            }

            curr[prev_ind + 1] = max(take, not_take);
        }
        next = curr;
    }

    return next[-1 + 1];
    // return statement
}
int lengthofLIS(vector<int> nums)
{
    int n = nums.size();
    // vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    // return memoization(0, nums, -1, n, dp);
    // return recursive(0, nums, -1, n);
    return spaceoptimisation(nums);
}
int main()
{
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Length of LIS is :- " << lengthofLIS(nums);
}

//TC -> O(n*n)
//SC -> O(n)