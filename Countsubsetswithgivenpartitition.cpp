/*Question :- We are given an array ‘ARR’ with N positive integers and an integer D.
We need to count the number of ways we can partition the given array into two subsets,
S1 and S2 such that S1 – S2 = D and S1 is always greater than or equal to S2.*/

#include <bits/stdc++.h>
using namespace std;

int tabulation(vector<int> &arr, int k, int d)
{
    int n = arr.size();
    vector<vector<bool>> dp(n, vector<bool>(k + 1, 0));
    for(int i = 0; i < n; i++)
        dp[i][0] = 1;
    
    if(arr[0] <= k)
        dp[0][arr[0]] = 1;
    
    for(int i = 1; i<n; i++){
        for(int target = 1; target <= k; target++)
        {
            bool not_taken = dp[i-1][target];
            bool taken = 0;
            if(arr[i] < target)
                taken = dp[i-1][target - arr[i]];
            dp[i][target] = taken || not_taken;
        }
    }
    int count = 0;
    for(int j = k/2 ; j >=0 ; j--)
        if(dp[n-1][j])
        {
            int diff = abs(k - 2*j);
            if(diff == d)
                count++;
        }
    
    return count;
}
int countpartitionswithgivendifference(vector<int> &arr, int diff)
{
    int sum = 0;
    for(auto x : arr)
        sum += x;
    int ans = tabulation(arr, sum, diff);
    return ans;
}

int main()
{
    vector<int> arr = {5, 2, 6, 4};
    int diff = 3;

    cout << "No of ways are :- " << countpartitionswithgivendifference(arr, diff);
}