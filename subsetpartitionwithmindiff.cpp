/*Question :- We are given an array ‘ARR’ with N positive integers.
We need to partition the array into two subsets such that the absolute difference of the sum of elements of the subsets is minimum.

We need to return only the minimum absolute difference of the sum of elements of the two partitions.*/

#include <bits/stdc++.h>
using namespace std;

// logic derived from equal sub partition problem
// we do fill up the dp table for target(column length) = sum
// for last row, we check from column ranging from "sum/2" to 0 ,
// the first cell to have true, we will have the ans as abs(sum - 2*j) where j is column number
int tabulation(int n, vector<int> &arr, int k)
{
    vector<vector<bool>> dp(n, vector<bool>(k + 1, false));
    // base-case
    for (int i = 0; i < n; i++)
        dp[i][0] = true;
    if (arr[0] <= k)
        dp[0][arr[0]] = true;

    // write for loops and do calculation
    for (int i = 1; i < n; i++)
        for (int target = 1; target <= k; target++)
        {
            bool not_taken = dp[i - 1][target];
            bool taken = false;
            if (arr[i] <= target)
                taken = dp[i - 1][target - arr[i]];

            dp[i][target] = taken || not_taken;
        }

    // return statement
    int ans = -1e9;
    for (int j = k / 2; j >= 0; j--)
        if (dp[n - 1][j])
        {
            ans = abs(k - 2 * j);
            break;
        }
    return ans;
}

bool spaceoptimised(int n, vector<int> &arr, int k)
{
    vector<bool> prev(k + 1, 0), curr(k + 1, 0);
    // base-cases
    prev[0] = curr[0] = true;
    if (arr[0] <= k)
        prev[arr[0]] = true;

    // write for loops and do calculation
    for (int i = 1; i < n; i++)
    {
        for (int target = 1; target <= k; target++)
        {
            bool not_taken = prev[target];
            bool taken = false;
            if (arr[i] <= target)
                taken = prev[target - arr[i]];

            curr[target] = taken || not_taken;
        }
        prev = curr;
    }
    // return statement

    int ans = -1e9;
    for (int j = k / 2; j >= 0; j--)
        if (prev[j])
        {
            ans = abs(k - 2 * j);
            break;
        }
    return ans;
}

int mindiffinpartition(vector<int> arr)
{
    // logic derived from equal sub partition problem
    // we do fill up the dp table for target(column length) = sum
    // for last row, we check from column ranging from "sum/2" to 0 ,
    // the first cell to have true, we will have the ans as abs(sum - 2*j) where j is column number

    int n = arr.size();
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];

    return spaceoptimised(n, arr, sum);
}
int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << mindiffinpartition(arr);
}

// TC -> o(n*k)
// SC -> o(n*k) or o(k)