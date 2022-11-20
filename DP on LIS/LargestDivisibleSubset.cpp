/*Question :- Given an array with distinct elements, we need to print its longest divisible subset. We can print any answer.*/
#include <bits/stdc++.h>
using namespace std;

void LDS(vector<int> nums)
{
    int n = nums.size();
    // since subset keeps no necessity of maintaining order so we can sort the array
    //  once array is sorted, finding Largest Divisble subset == Longest Divisible Subsequence as order doesnot matter anyway
    sort(nums.begin(), nums.end());
    vector<int> dp(n, 1), hash(n);
    int last_index = 0;
    int length_of_LDS = INT_MIN;
    // now we modify code for printing LIS to make it code for LDS
    hash.push_back(0);
    for (int i = 1; i < n; i++)
    {
        hash[i] = i;
        for (int j = 0; j < i; j++)
        {
            if (nums[i] % nums[j] == 0 && dp[i] < 1 + dp[j])
            {
                dp[i] = 1 + dp[j];
                hash[i] = j;
            }
        }

        if (dp[i] > length_of_LDS)
        {
            length_of_LDS = dp[i];
            last_index = i;
            
        }
    }

    vector<int> ans;
    ans.push_back(nums[last_index]);
    while (hash[last_index] != last_index)
    {
        last_index = hash[last_index];
        ans.push_back(nums[last_index]);
    }

    for (auto x : ans)
        cout << x << " ";
    cout << endl;
}
int main()
{
    vector<int> nums = {6,2,4,12,8,16,22,24};
    cout << "Largest Divisible Subset is " << endl;
    LDS(nums);
}

// TC -> O(n*n)
// SC -> O(n)