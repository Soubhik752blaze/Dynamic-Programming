/*Question :- You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions.*/

#include <bits/stdc++.h>
using namespace std;

// the same problem can be solved by approach shown in stockbuyandsell3 problem but here we are taking a slight different approach
// if there are k transactions possible, and if we count buy and sell individually as 1 transaction then we can make at most k*2 transactions
// we thus use cap as 2*k here
// Also we dont need the variable "buy" anymore as if cap is any time even then its a buy call else its a sell call.
int recursive(int i, int cap, vector<int> price, int n)
{
    // base case
    if (cap == 0 || i == n)
        return 0;
    // explore all possibilites
    int profit;
    // if we can buy
    if (cap % 2 == 0)
    {
        // we do buy or we dont buy
        profit = max(-price[i] + recursive(i + 1, cap - 1, price, n), recursive(i + 1, cap, price, n));
    }
    // else if we can sell
    else
    {
        // we do sell or we dont sell
        profit = max(price[i] + recursive(i + 1, cap - 1, price, n), recursive(i + 1, cap, price, n));
    }
    // return max profit
    return profit;
}

int memoization(int i, int cap, vector<int> price, int n, vector<vector<int>> &dp)
{
    // base case
    if (cap == 0 || i == n)
        return 0;
    if (dp[i][cap] != -1)
        return dp[i][cap];
    // explore all possibilites
    int profit;
    // if we can buy
    if (cap % 2 == 0)
    {
        // we do buy or we dont buy
        profit = max(-price[i] + memoization(i + 1, cap - 1, price, n, dp), memoization(i + 1, cap, price, n, dp));
    }
    // else if we can sell
    else
    {
        // we do sell or we dont sell
        profit = max(price[i] + memoization(i + 1, cap - 1, price, n, dp), memoization(i + 1, cap, price, n, dp));
    }
    // return max profit
    return dp[i][cap] = profit;
}

int tabulation(vector<int> price, int k)
{
    int n = price.size();
    vector<vector<int>> dp(n + 1, vector<int>(2 * k + 1, 0));

    // base case already taken care since all elements in the vector are already filled with 0
    for (int i = n - 1; i >= 0; i--)
        for (int cap = 1; cap <= 2*k; cap++)
        {
            int profit;
            if (cap % 2 == 0)
            {
                // we do buy or we dont buy
                profit = max(-price[i] + dp[i + 1][cap - 1], dp[i + 1][cap]);
            }
            else
            {
                // we do sell or we dont sell
                profit = max(price[i] + dp[i + 1][cap - 1], dp[i + 1][cap]);
            }
            // return max profit
            dp[i][cap] = profit;
        }

    return dp[0][2*k];
}

int spaceoptimisation(vector<int> price, int k)
{
    int n = price.size();
    vector<int> ahead(2 * k + 1, 0), curr(2 * k + 1, 0);

    // base case already taken care since all elements in the vector are already filled with 0
    for (int i = n - 1; i >= 0; i--){
        for (int cap = 1; cap <= 2*k; cap++)
        {
            int profit;
            if (cap % 2 == 0)
            {
                // we do buy or we dont buy
                profit = max(-price[i] + ahead[cap - 1], ahead[cap]);
            }
            else
            {
                // we do sell or we dont sell
                profit = max(price[i] + ahead[cap - 1], ahead[cap]);
            }
            // return max profit
            curr[cap] = profit;
        }
        ahead = curr;
    }

    return ahead[2*k];
}

int stockbuyandsell4(vector<int> price, int k)
{
    int n = price.size();
    // vector<vector<int>> dp (n + 1, vector<int> (2*k + 1, -1));
    // return memoization(0, 2*k, price, n, dp);
    return spaceoptimisation(price, k);
}

int main()
{
    vector<int> prices = {3,2,6,5,0,3};
    int k = 2;
    cout << "Max profit possible with at most K transactions is " << stockbuyandsell4(prices, k);
}
