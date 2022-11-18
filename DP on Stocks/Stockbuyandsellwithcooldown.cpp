/*Question:- You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:

After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day)..*/

#include <bits/stdc++.h>
using namespace std;

// this is same as stockbuyandsell2, the only difference being we cant do any transaction 1 day after selling\
// so after every sell, we now move the index by 2 and not by 1. since 1 more day counts for cooldown
// Accordingly base case now becomes i>= n
int recursive(int i, int buy, vector<int> price, int n)
{
    // base case
    if (i >= n)
        return 0;
    // explore all possibilites
    int profit;
    // if we can buy
    if (buy)
    {
        // we do buy or we dont buy
        profit = max(-price[i] + recursive(i + 1, 0, price, n), recursive(i + 1, 1, price, n));
    }
    // else if we can sell
    else
    {
        // we do sell or we dont sell
        profit = max(price[i] + recursive(i + 2, 1, price, n), recursive(i + 1, 0, price, n));
    }
    // return max profit
    return profit;
}

int memoization(int i, int buy, vector<int> price, int n, vector<vector<int>> &dp)
{
    // base case
    if (i >= n)
        return 0;

    if (dp[i][buy] != -1)
        return dp[i][buy];
    // explore all possibilites
    int profit;
    // if we can buy
    if (buy)
    {
        // we do buy or we dont buy
        profit = max(-price[i] + memoization(i + 1, 0, price, n, dp), memoization(i + 1, 1, price, n, dp));
    }
    // else if we can sell
    else
    {
        // we do sell or we dont sell
        profit = max(price[i] + memoization(i + 2, 1, price, n, dp), memoization(i + 1, 0, price, n, dp));
    }
    // return max profit
    return dp[i][buy] = profit;
}

int tabulation(vector<int> price)
{
    int n = price.size();
    vector<vector<int>> dp(n + 2, vector<int>(2, 0));
    // base case already taken care as all values already 0

    // general scenario
    for (int i = n - 1; i >= 0; i--)
    {
        dp[i][1] = max(-price[i] + dp[i + 1][0], dp[i + 1][1]);
        dp[i][0] = max(price[i] + dp[i + 2][1], dp[i + 1][0]);
    }

    // return scenario
    // we are returning for buy = 1 because at ind 0 we have the access to buy
    return dp[0][1];
}

int spaceoptimised(vector<int> price)
{
    int n = price.size();
    vector<int> ahead2(2, 0), ahead1(2, 0), curr(2, 0);
    // base case already taken care as all values already 0

    // general scenario
    for (int i = n - 1; i >= 0; i--)
    {
        curr[1] = max(-price[i] + ahead1[0], ahead1[1]);
        curr[0] = max(price[i] + ahead2[1], ahead1[0]);

        ahead2 = ahead1;
        ahead1 = curr;
    }

    // return scenario
    // we are returning for buy = 1 because at ind 0 we have the access to buy
    return curr[1];
}
int stockbuyandsellwithcooldwon(vector<int> price)
{
    int n = price.size();
    // vector<vector<int>> dp (n+2, vector<int> (2, -1));
    // return memoization(0, 1, price, n,dp);
    return spaceoptimised(price);
}

int main()
{
    vector<int> prices = {1, 2, 3, 0, 2};
    cout << "Max profit possible is " << stockbuyandsellwithcooldwon(prices);
}

// TC -> O(n*2) or o(n) incase the buy loop is removed as done in tabulation
// SC -> O(n*2) or o(1) incase of using space optimisation
