/*Question :- Given an integer array nums, Print the longest strictly increasing subsequence.*/

#include <bits/stdc++.h>
using namespace std;

//for printing length of LIS
vector<int> bestway(vector<int> nums)
{
    int n = nums.size();
    //dp[i] signifies length of LIS that ends at index i
    // hash[i] signifies all prev_ind for ith index LIS element
    vector<int> dp(n,1), hash(n);
    // last_index stores the last index of the LIS to be formed
    int length_LIS = INT_MIN;
    int last_index = 0;
    // general scenario
    for (int i = 0; i < n; i++){
        hash[i] = i;
        for (int prev = 0; prev < i; prev++)
        {
            if(nums[i] > nums[prev] && 1 + dp[prev] > dp[i])
                {
                    dp[i] = 1 + dp[prev];
                    hash[i] = prev;
                }
        }
        if(dp[i] > length_LIS)
        {
            length_LIS = dp[i];
            last_index = i;
        }
    }  
    // we create a vector "ans" inside of which we will store all the LIS elements in reverse fashion and in the end reverse it
    // we take help of the vector "hash" here which has all prev_indexes of the elements stored
    // we find the LIS last element by using last_index variable and use it to backtrack the entire LIS 
    vector<int> ans;
    ans.push_back(nums[last_index]);
    while(hash[last_index] != last_index)
    {
        last_index = hash[last_index];
        ans.push_back(nums[last_index]);
    }
    reverse(ans.begin(), ans.end());
    return ans;

}
void lengthofLIS(vector<int> nums)
{
    vector<int> ans = bestway(nums);
    for(auto x : ans)
        cout << x << " ";
}
int main()
{
    vector<int> nums = {5,4,11,1,16,8};
    lengthofLIS(nums);
}

//TC -> O(n*n)
//SC -> O(n)