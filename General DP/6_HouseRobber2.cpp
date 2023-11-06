/*Question:- You are a professional robber planning to rob houses along a street.
Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected
it will automatically contact the police if two adjacent houses were broken into on the same night.
All houses are connected in a circle i.e last and first houses are neighbouring houses.

Given an integer array nums representing the amount of money of each house,
return the maximum amount of money you can rob tonight without alerting the police.
*/
#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> arr)
{
    // If we start from beginning, then for every step we have "pick" or "notpick" option
    // Pick = arr[i] + x1, where x1 is the max sum up until arr[i] excluding its adjacent prev element
    // Not Pick = 0 + x2, where arr[i] is not selected and x2 is the max sum up untill arr[i] including its adjacent prev element and excluding arr[i]
    // for every step, we choose the max out of "pick" and "notpick" then we cumulate the results in this way upto n-1th element
    int n = arr.size();
    int *dp = new int[n];
    dp[0] = arr[0];
    dp[1] = max(arr[0], arr[1]);
    for (int i = 2; i < n; i++)
    {
        int pick = arr[i] + dp[i - 2];
        int notpick = 0 + dp[i - 1];
        dp[i] = max(pick, notpick);
    }
    return dp[n - 1];
}

int maxrobbery(vector<int> arr)
{
    // we create 2 seperate vectors one excluding first element another excluding last element
    // we use solve functions on both the vectors, and take the max. of both results obtained
    int n = arr.size();
    if (n == 1)
        return arr[0];
    vector<int> temp1, temp2;
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
            temp1.push_back(arr[i]);
        if (i != n - 1)
            temp2.push_back(arr[i]);
    }
    int pick1 = solve(temp1);
    int pick2 = solve(temp2);
    return max(pick1, pick2);
}
int main()
{
    vector<int> arr{2, 1, 4, 9};
    cout << maxrobbery(arr);
}
// 1D DP problem
// SC -> o(n) can be made o(1) by using variables
// TC -> o(n)