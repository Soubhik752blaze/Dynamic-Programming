/*Question :- We are given an array ‘ARR’ with N positive integers (>= 0) and an integer K.
We need to find the number of subsets whose sum is equal to K. */

#include <bits/stdc++.h>
using namespace std;

int recursive(int i, int target, vector<int> &arr)
{
    // base case
    // if the target is achieved we increase count by 1 or if we have go beyond last index, we return 0;
    // 
    if (target == 0)
        return 1;
    if (i == 0)
        return arr[i] == target;

    // traversal or calculation
    // either we pick the element in our required subsequence or we dont
    //  we pick it only if its less than the required target now
    int not_taken = recursive(i - 1, target, arr);
    int taken = 0;
    if (arr[i] <= target)
        taken = recursive(i - 1, target - arr[i], arr);

    // return statement
    return taken + not_taken;
}

int memoization(int i, int target, vector<int> &arr, vector<vector<int>> &dp)
{
    // base case
    // if the target is achieved we return true or if we have reached last index, we check if target is achieved
    // includes logic for if element is  0
    if (i == 0)
    {
        if(target == 0 && arr[0] == 0)
            return 2;
        if(target == 0 || target == arr[0])
            return 1;
        return 0;
    }
    // if answer already exists, we dont recalculate it
    if (dp[i][target] != -1)
        return dp[i][target];

    int not_taken = memoization(i - 1, target, arr, dp);
    int taken = 0;
    if (arr[i] <= target)
        taken = memoization(i - 1, target - arr[i], arr, dp);
    

    // return statement
    return dp[i][target] = (taken + not_taken);
}

int tabulation(int n, int k, vector<int> &arr)
{
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));
    // base-case
    for (int i = 0; i < n; i++)
        dp[i][0] = 1;
    if (arr[0] <= k)
        dp[0][arr[0]] = 1;

    // write for loops and do calculation
    for (int i = 1; i < n; i++)
        for (int target = 1; target <= k; target++)
        {
            int not_taken = dp[i - 1][target];
            int taken = 0;
            if (arr[i] <= target)
                taken = dp[i - 1][target - arr[i]];

            dp[i][target] = taken + not_taken;
        }

    // return statement
    return dp[n - 1][k];
}

int spaceoptimised(int n, int k, vector<int> &arr)
{
    vector<int> prev(k + 1, 0), curr(k + 1, 0);
    // base-cases
    prev[0] = curr[0] = 1;
    if (arr[0] <= k)
        prev[arr[0]] = 1;

    // write for loops and do calculation
    for (int i = 1; i < n; i++)
    {
        for (int target = 1; target <= k; target++)
        {
            int not_taken = prev[target];
            int taken = 0;
            if (arr[i] <= target)
                taken = prev[target - arr[i]];

            curr[target] = taken + not_taken;
        }
        prev = curr;
    }
    // return statement
    return prev[k];
}

int countsubsetswithsumk(int target, vector<int> &arr)
{
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    int ans = memoization(n - 1, target, arr, dp);
    return ans;
}
int main()
{
    vector<int> arr = {0,0,1};
    int k = 1;
    cout << "No of subsets found are " << countsubsetswithsumk(k, arr);
}

// TC -> O(N*K)
// SC -> O(N*K) or O(K)


