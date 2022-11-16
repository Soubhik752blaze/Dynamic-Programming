/*Question :- You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete at most two transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).*/

#include <bits/stdc++.h>
using namespace std;

// this is same as stockbuyandsell2 but here a cap is given of at max 2 transactions
// cap is reduced to cap - 1 when 1 successful transaction occurs(when stock is sold, because for selling already buying is must)
int recursive(int i, int buy, int cap, vector<int> price, int n)
{
    // base case
    if (cap == 0 || i == n)
        return 0;
    // explore all possibilites
    int profit;
    // if we can buy
    if (buy)
    {
        // we do buy or we dont buy
        profit = max(-price[i] + recursive(i + 1, 0, cap, price, n), recursive(i + 1, 1, cap, price, n));
    }
    // else if we can sell
    else
    {
        // we do sell or we dont sell
        profit = max(price[i] + recursive(i + 1, 1, cap - 1, price, n), recursive(i + 1, 0, cap, price, n));
    }
    // return max profit
    return profit;
}

int memoization(int i, int buy, int cap, vector<int> price, int n, vector<vector<vector<int>>> &dp)
{
    // base case
    if (i == n || cap == 0)
        return 0;

    if (dp[i][buy][cap] != -1)
        return dp[i][buy][cap];
    // explore all possibilites
    int profit;
    // if we can buy
    if (buy)
    {
        // we do buy or we dont buy
        profit = max(-price[i] + memoization(i + 1, 0, cap, price, n, dp), memoization(i + 1, 1, cap, price, n, dp));
    }
    // else if we can sell
    else
    {
        // we do sell or we dont sell
        profit = max(price[i] + memoization(i + 1, 1, cap - 1, price, n, dp), memoization(i + 1, 0, cap, price, n, dp));
    }
    // return max profit
    return dp[i][buy][cap] = profit;
}

int tabulation(vector<int> &price)
{
    int n = price.size();
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(3, 0)));
    // base case is already taken care of since every value is already 0

    // general scenario
    for (int i = n - 1; i >= 0 ; i--)
        for (int buy = 1; buy >= 0; buy--)
            for (int cap = 1; cap <= 2; cap++)
            {
                int profit;
                if (buy)
                {
                    // we do buy or we dont buy
                    profit = max(-price[i] + dp[i + 1][0][cap], dp[i + 1][1][cap]);
                }
                else
                {
                    // we do sell or we dont sell
                    profit = max(price[i] + dp[i + 1][1][cap - 1], dp[i + 1][0][cap]);
                }
                
                dp[i][buy][cap] = profit;
            }

    return dp[0][1][2];
}

int spaceoptimisation(vector<int> &price)
{
    int n = price.size();
    vector<vector<int>> ahead(2, vector<int>(3, 0)), curr(2, vector<int>(3, 0));
    // base case is already taken care of since every value is already 0

    // general scenario
    for (int i = n - 1; i >= 0 ; i--){
        for (int buy = 1; buy >= 0; buy--){
            for (int cap = 1; cap <= 2; cap++)
            {
                int profit;
                if (buy)
                {
                    // we do buy or we dont buy
                    profit = max(-price[i] + ahead[0][cap], ahead[1][cap]);
                }
                else
                {
                    // we do sell or we dont sell
                    profit = max(price[i] + ahead[1][cap - 1], ahead[0][cap]);
                }
                
                curr[buy][cap] = profit;
            }
        }
        ahead = curr;
    }

    return ahead[1][2];
}

int stockbuyandsell3(vector<int> price)
{
    int n = price.size();
    // vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1)));
    // return memoization(0, 1, 2, price, n, dp);
    return spaceoptimisation(price);
}

int main()
{
    vector<int> prices = {3,3,5,0,0,3,1,4};
    cout << "Max profit possible is " << stockbuyandsell3(prices);
}
