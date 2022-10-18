/*Question :- We are given an array ‘ARR’ with N positive integers and an integer D.
We need to count the number of ways we can partition the given array into two subsets,
S1 and S2 such that S1 – S2 = D and S1 is always greater than or equal to S2.*/

#include <bits/stdc++.h>
using namespace std;

/* we have s1 - s2 = D
Also, s1 + s2 = sum
So, S2 = (sum - D)/2 So this is just the problem of count subset with target k
with edge cases being :-
    1. (sum - D) > 0
    2. (sum - D) % 2 must be 0 as s2 cant be fraction */

int recursive(int i, vector<int> &arr, int target)
{
    // includes base case of element can be 0 as well
    if (i == 0)
    {
        if (target == 0 && arr[i] == 0)
            return 2; // 2 cases -pick and not pick
        if (target == 0 || arr[i] == target)
            return 1; // 1 case - not pick
        return 0;     // 1 case -pick
    }

    int not_taken = recursive(i - 1, arr, target);
    int taken = 0;
    if (arr[i] <= target)
        taken = recursive(i - 1, arr, target - arr[i]);
    return taken + not_taken;
}

int memoization(int i, vector<int> &arr, int target, vector<vector<int>> &dp)
{
    // includes base case of element can be 0 as well
    if (i == 0)
    {
        if (target == 0 && arr[i] == 0)
            return 2; // 2 cases -pick and not pick
        if (target == 0 || arr[i] == target)
            return 1; // 1 case - not pick or 1 case - pick
        return 0;     
    }

    if (dp[i][target] != -1)
        return dp[i][target];
    int not_taken = memoization(i - 1, arr, target, dp);
    int taken = 0;
    if (arr[i] <= target)
        taken = memoization(i - 1, arr, target - arr[i], dp);
    return dp[i][target] = taken + not_taken;
}
int tabulation(vector<int> &num, int k)
{
    int n = num.size();

    vector<vector<int>> dp(n, vector<int>(k + 1, 0));

    if (num[0] == 0)
        dp[0][0] = 2; // 2 cases -pick and not pick
    else
        dp[0][0] = 1; // 1 case - not pick

    if (num[0] != 0 && num[0] <= k)
        dp[0][num[0]] = 1; // 1 case -pick

    for (int ind = 1; ind < n; ind++)
    {
        for (int target = 0; target <= k; target++)
        {

            int notTaken = dp[ind - 1][target];

            int taken = 0;
            if (num[ind] <= target)
                taken = dp[ind - 1][target - num[ind]];

            dp[ind][target] = (notTaken + taken);
        }
    }
    return dp[n - 1][k];
}
int countpartitionswithgivendifference(vector<int> &arr, int diff)
{
    int n = arr.size();
    int sum = 0;
    for (auto x : arr)
        sum += x;
    if (sum < diff || (sum - diff) % 2)
        return false;
    vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
    int ans = tabulation(arr, (sum - diff) / 2);
    return ans;
}

int main()
{
    vector<int> arr = {1, 2, 3, 1, 2};
    int diff = 1;

    cout << "No of ways are :- " << countpartitionswithgivendifference(arr, diff);
}

//TC -> O(N*K)
//SC -> o(N*K) or O(K) if space optimised