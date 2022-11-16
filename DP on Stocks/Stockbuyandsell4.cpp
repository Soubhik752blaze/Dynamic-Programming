/*Question :- You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions.*/

#include <bits/stdc++.h>
using namespace std;

// this is same as stockbuyandsell3 but here a cap is given of at max k transactions
// cap is reduced to cap - 1 when 1 successful transaction occurs
int recursive(int i, int buy, int cap, vector<int> price, int n)
{
    // base case
    if( cap == 0 )
        return 0;
    if (i == n)
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
int stockbuyandsell4(vector<int> price, int k)
{
    int n = price.size();
    // vector<vector<int>> dp (n+1, vector<int> (2, -1));
    return recursive(0, 1, k, price, n);
    //return spaceoptimised(price);
}

int main()
{
    vector<int> prices = {2,4,1};
    int k = 2;
    cout << "Max profit possible is " << stockbuyandsell4(prices, k);
}
