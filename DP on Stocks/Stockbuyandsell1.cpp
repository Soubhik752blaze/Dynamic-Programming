/*Question:- You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.*/

#include<bits/stdc++.h>
using namespace std;

// intution for every day stock price, keep a track of the min stock price day before it
// that will give the max profit for buying a stock before and selling on that day
// keep a track of max profit possible
int stockbuyandsell1(vector<int> price)
{
    int cost = price[0];
    int profit = 0, max_profit = 0;
    int n = price.size();
    for(int i = 1; i < n; i++)
    {
        profit = price[i] - cost;
        if( profit > max_profit)
            max_profit = profit;
        cost = min(cost, price[i]);
    }
    return max_profit;
}

int main()
{
    vector<int> prices = {7,1,5,3,6,4};
    cout << "Max profit possible is " << stockbuyandsell1(prices);
}

// TC -> O(n)
// SC -> O(1)