/*Question:- Given a number of stairs and a frog, the frog wants to climb from the 0th stair to the (N-1)th stair.
At a time the frog can climb either k ( 1,2,3,...K) steps. A height[N] array is also given.
Whenever the frog jumps from a stair i to stair j, the energy consumed in the jump is abs(height[i]- height[j]), where abs() means the absolute difference.
We need to return the minimum energy that can be used by the frog to jump from stair 0 to stair N-1.
*/
#include <bits/stdc++.h>
using namespace std;

int frogjumpwithk(vector<int> height, int k)
{
    // the goal is to reach the n-1th step
    // once we are at a particular step, we can reach next step ( +1 or +2 or +k) by giving the cost[next_step] - cost[current_step]
    // we choose the one which is minimum cost for every step (by having a loop from 1 to k and having the min cost calculated out of k steps and storing the answer)
    // so by dp, we find the min cost to reach for every step up until n-1th step by taking min cost at each step
    int n = height.size();
    int *dp = new int[n];
    dp[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int minsteps = INT_MAX;
        for (int j = 1; j <=k; j++)
        {
            int step = dp[i - j] + abs(height[i] - height[i-j]);
            minsteps = min(minsteps,step);
        }
        dp[i] = minsteps;
    }
    return dp[n - 1];
}
int main()
{
    vector<int> height = {30, 10, 60, 10, 60, 50};
    int k = 2;
    cout << frogjumpwithk(height, k);
    return 0;
}
// SC -> o(n)    
// TC -> o(n*K)