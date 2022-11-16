/*Question:- You are given an integer array prices where prices[i] is the price of a given stock on the ith day.

On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of the stock at any time.
However, you can buy it then immediately sell it on the same day.

Find and return the maximum profit you can achieve.*/

#include <bits/stdc++.h>
using namespace std;

// there are multiple ways of buy and sell, since we have to try multiple ways we will go for recursion
// this function tells us upto ith day, whats the max profit possible to make
// parameters - i(index), buy(variable to check if buying is possible or not) and price(input)
int recursive(int i, int buy, vector<int> price, int n)
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
        profit = max(-price[i] + recursive(i + 1, 0, price, n), recursive(i + 1, 1, price, n));
    }
    // else if we can sell
    else
    {
        // we do sell or we dont sell
        profit = max(price[i] + recursive(i + 1, 1, price, n), recursive(i + 1, 0, price, n));
    }
    // return max profit
    return profit;
}

int memoization(int i, int buy, vector<int> price, int n, vector<vector<int>> &dp)
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
        profit = max(-price[i] + memoization(i + 1, 0, price, n, dp), memoization(i + 1, 1, price, n, dp));
    }
    // else if we can sell
    else
    {
        // we do sell or we dont sell
        profit = max(price[i] + memoization(i + 1, 1, price, n, dp), memoization(i + 1, 0, price, n, dp));
    }
    // return max profit
    return dp[i][buy] = profit;
}

int tabulation(vector<int> price)
{
    int n = price.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));

    // base case
    dp[n][0] = dp[n][1] = 0;

    // general scenario
    for (int i = n - 1; i >= 0; i--)
    {
        for (int buy = 1; buy >= 0; buy--)
        {
            int profit = 0;
            if (buy)
            {
                // we do buy or we dont buy
                profit = max(-price[i] + dp[i + 1][0], dp[i + 1][1]);
            }
            // else if we can sell
            else
            {
                // we do sell or we dont sell
                profit = max(price[i] + dp[i + 1][1], dp[i + 1][0]);
            }
            dp[i][buy] = profit;
        }
    }

    // return scenario
    // we are returning for buy = 1 because at ind 0 we have the access to buy
    return dp[0][1];    
}

int spaceoptimised(vector<int> price)
{
    int n = price.size();
    vector<int> ahead(2, 0), curr(2,0);

    // base case
    ahead[0] = ahead[1] = 0;

    // general scenario
    for (int i = n - 1; i >= 0; i--)
    {
        for (int buy = 1; buy >= 0; buy--)
        {
            int profit = 0;
            if (buy)
            {
                // we do buy or we dont buy
                profit = max(-price[i] + ahead[0], ahead[1]);
            }
            // else if we can sell
            else
            {
                // we do sell or we dont sell
                profit = max(price[i] + ahead[1], ahead[0]);
            }
            curr[buy] = profit;
        }
        ahead = curr;
    }

    // return scenario
    // we are returning for buy = 1 because at ind 0 we have the access to buy
    return ahead[1];    
}
int stockbuyandsell2(vector<int> price)
{
    int n = price.size();
    // vector<vector<int>> dp (n+1, vector<int> (2, -1));
    // return memoization(0, 1, price, n,dp);
    return spaceoptimised(price);
}

int main()
{
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "Max profit possible is " << stockbuyandsell2(prices);
}

// TC -> O(n*2)
// SC -> O(n*2) or o(1) incase of using space optimisation

// Best TC is o(n) and SC o(1) by the following code :-
/* int profit = 0;
        for(int i=1;i<prices.size();i++)
            if(prices[i]>prices[i-1])
                profit+=prices[i]-prices[i-1];
        return profit;
*/