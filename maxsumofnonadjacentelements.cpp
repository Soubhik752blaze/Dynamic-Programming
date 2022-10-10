/*Question:- Given an array of ‘N’  positive integers, we need to return the maximum sum of the subsequence
such that no two elements of the subsequence are adjacent elements in the array.

Note: A subsequence of an array is a list with elements of the array where some elements are deleted ( or not deleted at all)
The elements should be in the same order in the subsequence as in the array.
Eg :- {2,1,4,9} => Output = 11
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
    dp[1] = max(arr[0],arr[1]);
    for(int i = 2; i < n; i++)
    {
        int pick = arr[i] + dp[i-2];
        int notpick = 0 + dp[i-1];
        dp[i] = max(pick, notpick);
    }
    return dp[n-1];
}
int main()
{
    vector<int> arr{2, 1, 4, 9};
    cout << solve(arr);
}
// 1D DP problem
// Also known as house robber problem
// SC -> o(n) can be made o(1)
// TC -> o(n)