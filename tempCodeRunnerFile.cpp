/*Question:- Given a number of stairs and a frog, the frog wants to climb from the 0th stair to the (N-1)th stair.
At a time the frog can climb either 1 or 2 steps. A height[N] array is also given.
Whenever the frog jumps from a stair i to stair j, the energy consumed in the jump is abs(height[i]- height[j]), where abs() means the absolute difference.
We need to return the minimum energy that can be used by the frog to jump from stair 0 to stair N-1.

*/
#include <bits/stdc++.h>
using namespace std;

int frogjump(vector<int> height)
{
    // the goal is to reach the n-1th step
    // once we are at a particular step, we can reach next step ( +1 or +2 ) by giving the cost[next_step] - cost[current_step]
    // we choose the one which is minimum cost
    // so by dp, we find the min cost to reach for every step up until n-1th step by taking min cost at each step
    int n = height.size();
    vector<int> dp(n, -1);
    dp[0] = 0;
    for (int ind = 1; ind < n; ind++)
    {
        int jumpTwo = INT_MAX;
        int jumpOne = dp[ind - 1] + abs(height[ind] - height[ind - 1]);
        if (ind > 1)
            jumpTwo = dp[ind - 2] + abs(height[ind] - height[ind - 2]);

        cout<<dp[ind];
        dp[ind] = min(jumpOne, jumpTwo);
    }
    cout << dp[n - 1];
}

int main()
{
    vector<int> height = {30, 10, 60, 10, 60, 50};
    cout << frogjump(height);
    return 0;
}

// variation of climb stairs problem
// SC -> o(n)    can be again decreased to o(1) by using variables inplace of array
// TC -> o(n)