/*Question :- You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums.
You are asked to burst all the balloons.
If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins.
If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.
Return the maximum coins you can collect by bursting the balloons wisely.*/

// VIDEO_EXPLANATION :- https://www.youtube.com/watch?v=Yz4LlDSlkns&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=52
#include <bits/stdc++.h>
using namespace std;

// Intuition :- since multiple patterns bring multiple results, this might be based on Partition DP
// we cant just burst a balloon from first and then solve partitions on left and right, because left partition might have dependencuy on balloons present in right partition
// Thus, the partitions cant be solved independently
// To solve them independently, we can select the last balloon to be popped (and then second last and then third last and so on) and then solved partitions independently.
// this is possible because if we know who we burst at last then we know in the second last burst, the dependency remains on which balloon (last one) and it is no more uncertain.
// If still unclear, you can refer to above video link.
int recursive(int i, int j, vector<int> balloons)
{
    // base case
    if (i > j)
        return 0;
    // try all possibilities

    int maxi = INT_MIN;
    // balloons[k] is to be last balloon to be burst in that partition
    for (int k = i; k <= j; k++)
    {
        int coins = (balloons[i - 1] * balloons[k] * balloons[j + 1]) + recursive(i, k - 1, balloons) + recursive(k + 1, j, balloons);
        maxi = max(maxi, coins);
    }

    // return best possible ans
    return maxi;
}

int memoization(int i, int j, vector<int> balloons, vector<vector<int>> &dp)
{
    // base case
    if (i > j)
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    // try all possibilities

    int maxi = INT_MIN;
    // balloons[k] is to be last balloon to be burst in that partition
    for (int k = i; k <= j; k++)
    {
        int coins = (balloons[i - 1] * balloons[k] * balloons[j + 1]) + memoization(i, k - 1, balloons, dp) + memoization(k + 1, j, balloons, dp);
        maxi = max(maxi, coins);
    }

    // return best possible ans
    return dp[i][j] = maxi;
}

int tabulation(vector<int> balloons, int n)
{
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    for (int i = n; i >= 1; i--)
        for (int j = i; j <= n; j++)
        {
            // base case already covered with all elements already 0
            // general scenario
            int maxi = INT_MIN;
            for (int k = i; k <= j; k++)
            {
                int coins = (balloons[i - 1] * balloons[k] * balloons[j + 1]) + dp[i][k - 1] + dp[k + 1][j];
                maxi = max(maxi, coins);
            }
            dp[i][j] = maxi;
        }

    return dp[1][n];
}
int burstballoons(vector<int> balloons)
{
    int n = balloons.size();
    // to take care of edge cases (no balloons at edges)
    balloons.push_back(1);
    balloons.insert(balloons.begin(), 1);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    // int ans = memoization(1, n, balloons, dp);
    int ans = tabulation(balloons, n);
    return ans;
}
int main()
{
    vector<int> balloons = {3, 1, 5, 8};
    cout << "Max coins possible is " << burstballoons(balloons);
}

// Hard to Intuitively find the answer
// sort of a pattern to keep in mind
// TC -> O(n*n*n)
// SC -> O(n*n)