/*Question:- You are given an array prices where prices[i] is the price of a given stock on the ith day, and an integer fee representing a transaction fee.

Find the maximum profit you can achieve.
You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.*/

#include <bits/stdc++.h>
using namespace std;

// this is same as stockbuyandsell2, the only difference being now after every sell we need to add -k as a transaction fee.
int recursive(int i, int buy, vector<int> price, int n, int k)
{
    // base case
    if (i == n)
        return 0;
    // explore all possibilites
    int profit;
    // if we can buy
    if (buy)
    {
        // we do buy or we dont buy
        profit = max(-price[i] + recursive(i + 1, 0, price, n, k), recursive(i + 1, 1, price, n, k));
    }
    // else if we can sell
    else
    {
        // we do sell or we dont sell
        profit = max(price[i] - k + recursive(i + 1, 1, price, n, k), recursive(i + 1, 0, price, n, k));
    }
    // return max profit
    return profit;
}

int memoization(int i, int buy, vector<int> price, int n, int k, vector<vector<int>> &dp)
{
    // base case
    if (i == n)
        return 0;

    if (dp[i][buy] != -1)
        return dp[i][buy];
    // explore all possibilites
    int profit;
    // if we can buy
    if (buy)
    {
        // we do buy or we dont buy
        profit = max(-price[i] + memoization(i + 1, 0, price, n, k, dp), memoization(i + 1, 1, price, n, k, dp));
    }
    // else if we can sell
    else
    {
        // we do sell or we dont sell
        profit = max(price[i] - k + memoization(i + 1, 1, price, n, k, dp), memoization(i + 1, 0, price, n, k, dp));
    }
    // return max profit
    return dp[i][buy] = profit;
}

int tabulation(vector<int> price, int k)
{
    int n = price.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    // base case already taken care as all values already 0

    // general scenario
    for (int i = n - 1; i >= 0; i--)
    {
        dp[i][1] = max(-price[i] + dp[i + 1][0], dp[i + 1][1]);
        dp[i][0] = max(price[i] - k + dp[i + 1][1], dp[i + 1][0]);
    }

    // return scenario
    // we are returning for buy = 1 because at ind 0 we have the access to buy
    return dp[0][1];
}

int spaceoptimised(vector<int> price, int k)
{
    int n = price.size();
    vector<int> ahead(2, 0), curr(2,0);
    // base case already taken care as all values already 0

    // general scenario
    for (int i = n - 1; i >= 0; i--)
    {
        curr[1] = max(-price[i] + ahead[0], ahead[1]);
        curr[0] = max(price[i] - k + ahead[1], ahead[0]);

        ahead = curr;
    }

    // return scenario
    // we are returning for buy = 1 because at ind 0 we have the access to buy
    return ahead[1];
}
int stockbuyandsellwithfee(vector<int> price, int k)
{
    int n = price.size();
    // vector<vector<int>> dp (n+1, vector<int> (2, -1));
    // return memoization(0, 1, price, n, k, dp);
    // // return recursive(0, 1, price, n, k);
    return spaceoptimised(price, k);
}

int main()
{
    vector<int> prices = {1, 3, 2, 8, 4, 9};
    int k = 2;
    cout << "Max profit possible is " << stockbuyandsellwithfee(prices, k);
}

// TC -> O(n*2) or o(n) incase the buy loop is removed as done in tabulation
// SC -> O(n*2) or o(1) incase of using space optimisation
