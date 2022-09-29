/*Question:- You are given an integer array cost where cost[i] is the cost of ith step on a staircase. 
Once you pay the cost, you can either climb one or two steps.

You can either start from the step with index 0, or the step with index 1.

Return the minimum cost to reach the top of the floor.

*/
#include <bits/stdc++.h>
using namespace std;

int minCostClimbingStairs(vector<int>& cost) {
        //the goal is to reach the n-1th step or n-2thstep 
        //once you pay the cost for that step, we can reach top
        //so by dp we find the min cost to reach for every step upto n-1th step
        //At last, we can take the min of last 2 steps(n-1 and n-2) since the top is accessible from those 2 steps
        int n = cost.size();
        int *dp = new int[n];
        dp[0] = cost[0];
        dp[1] = cost[1];
        for(int i = 2; i<n ; i++)
            dp[i] = cost [i] + min(dp[i-1], dp[i-2]);
            
        return min(dp[n-1],dp[n-2]);
    }

int main()
{
    vector<int> cost = {10,15,20};
    cout << minCostClimbingStairs(cost);
    return 0;
}

//variation of climb stairs problem
//SC -> o(n)    can be again decreased to o(1) by using variables inplace of array
//TC -> o(n)