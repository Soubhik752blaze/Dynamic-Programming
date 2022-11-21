/*Question:- Given an array of positive integers. Find the maximum length of Bitonic subsequence.
A subsequence of array is called Bitonic if it is first strictly increasing, then strictly decreasing.*/

#include <bits/stdc++.h>
using namespace std;
int lengthLBS(vector<int> nums)
{
    int n = nums.size();
    // dp1 is for forward LIS, dp2 is for backware LIS
    vector<int> dp1(n, 1), dp2(n, 1);
    for (int i = 0; i < n; i++)
    {
        for (int prev = 0; prev < i; prev++)
        {
            if (nums[i] > nums[prev] && 1 + dp1[prev] > dp1[i])
                dp1[i] = 1 + dp1[prev];
        }
    }
    //dp2 is basically LDS (longest Decreasing Subsequence) as LIS from backwards  == LDS
    for (int i = n - 2; i >= 0; i--)
    {
        for (int prev = n - 1; prev >= i; prev--)
        {
            if (nums[i] > nums[prev] && 1 + dp2[prev] > dp2[i])
                dp2[i] = 1 + dp2[prev];
        }
    }

    //largest Bitonic array length would be the length of LIS + LDS with common pivot point i.e max of dp1[i] + dp2[i] - 1 (-1 for the common element at ith index being included 2 times)
    int ans = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int temp = dp1[i] + dp2[i] - 1;
        ans = max(temp, ans);
    }
    return ans;
}
int main()
{
    vector<int> nums = {2, 1, 1, 5, 6, 2, 3, 1};

    cout << "length of the longest bitonic subsequence is "<< lengthLBS(nums);
}

// TC -> O(N*N)
// SC -> O(N)