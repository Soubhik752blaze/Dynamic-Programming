/*Question :- Given an integer array nums, return the number of longest increasing subsequences.

Notice that the sequence has to be strictly increasing.*/

#include<bits/stdc++.h>
using namespace std;

//For more detailed explanation on this problem, see this video :- https://www.youtube.com/watch?v=cKVl1TFdNXg&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=48
int noofLIS(vector<int> arr)
{
    // so first thing :- we have to find LIS from given vector and then count of all possible LIS
    int n  = arr.size();
    vector<int> dp(n,1), count(n,1);
    int LIS = 1;

    // while calculating the dp array for LIS, we keep a count array telling how many LIS are present
    // so we keep a simple check that if dp[i] == 1 + dp[j] that means that it is also a LIS.. so just add count[j] to count[i]
    // This is because all prev LIS ending at arr[j] can form LIS including arr[i] to have same length LIS, thus increasing count by count[j]
    // Also, if dp[i] > 1 + dp[j], then we have a new LIS length so take count[i] = count[j]
    // This is because all prev LIS ending at arr[j] can form LIS with arr[i] being a part of it as well and forming the longest LIS now
    for(int i  = 1; i<n; i++){
        for(int j = 0; j < i; j++)
        {
            if(arr[i] > arr[j])
                {
                    if(dp[i] < 1 + dp[j])
                        {
                            dp[i] = dp[j] + 1;
                            count[i] = count[j];
                        }
                    else if(dp[i] == 1 + dp[j])
                        {
                            count[i] += count[j];
                        }
                }
        }
        LIS = max(LIS, dp[i]);
    }

    int ans = 0;
    for(int i = 0 ;i<n;i++)
    {
        if( dp[i] == LIS)
            ans += count[i];
    }
    return ans;
}
int main()
{
    vector<int> nums = {2,2,2,2,2};
    cout << " Total number of longest increasing subsequences are " << noofLIS(nums);
}
    

