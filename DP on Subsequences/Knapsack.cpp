/*Question :- A thief wants to rob a store.
He is carrying a bag of capacity W. The store has ‘n’ items.
Its weight is given by the ‘wt’ array and its value by the ‘val’ array.
He can either include an item in its knapsack or exclude it but can’t partially have it as a fraction.
We need to find the maximum value of items that the thief can steal.*/

#include <bits/stdc++.h>
using namespace std;

// at each instance, we have two 2 choices pick or not pick the item
//  if we pick, we add the value to the result and subtract its weight from total weight allowed, then move on to next item
//  if we dont pick, we add no value to result and move on to the next item
int recursion(int i, vector<int> &wt, vector<int> &val, int weight)
{
    // basecase
    if (i == 0)
    {
        if (wt[0] <= weight)
            return val[0];
        else
            return 0;
    }
    // explore all possibilites
    int not_take = 0 + recursion(i - 1, wt, val, weight);
    int take = INT_MIN;
    if (wt[i] <= weight)
        take = val[i] + recursion(i - 1, wt, val, weight - wt[i]);

    // return max
    return max(not_take, take);
}

int tabulation(vector<int> &wt, vector<int> &val, int W)
{

    int n = val.size();
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));
    // base case
    for (int i = wt[0]; i <= W; i++)
        dp[0][i] = val[0];

    // for loop calcaltion
    for (int i = 1; i < n; i++)
        for (int weight = 0; weight <= W; weight++)
        {
            int not_taken = dp[i - 1][weight];
            int taken = INT_MIN;
            if (wt[i] <= weight)
                taken = val[i] + dp[i - 1][weight - wt[i]];

            dp[i][weight] = max(taken, not_taken);
        }
    // return
    return dp[n - 1][W];
}

int spaceoptimised(vector<int> &wt, vector<int> &val, int W)
{

    int n = val.size();
    vector<int> prev(W + 1, 0);
    // base case
    for (int i = wt[0]; i <= W; i++)
        prev[i] = val[0];

    for (int i = 1; i < n; i++)
        for (int weight = W; weight >= 0; weight--)
        {
            int not_taken = prev[weight];
            int taken = INT_MIN;
            if (wt[i] <= weight)
                taken = val[i] + prev[weight - wt[i]];

            prev[weight] = max(taken, not_taken);
        }

    return prev[W];
}

int knapsack(vector<int> &wt, vector<int> &val, int weight)
{
    int n = wt.size();
    int ans = spaceoptimised(wt, val, weight);
    return ans;
}

int main()
{
    vector<int> wt = {2, 3, 5};
    vector<int> val = {40, 50, 60};
    int W = 8;

    cout << "The Maximum value of items, thief can steal is " << knapsack(wt, val, W);
    return 0;
}

// TC -> o(N*W)
// SC -> o(N*W) or O(W)