/*Question :- Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack.
 In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which represent values and weights associated with n items respectively.
 Also given an integer W which represents knapsack capacity, find the maximum value subset of val[] such that sum of the weights of this subset is >=  W. 
 You cannot break an item, either pick the complete item or don’t pick it (0-1 property).*/

#include <bits/stdc++.h>
using namespace std;

int t[100][100];


int knapsack(int wt[], int val[], int w, int n)
{   
    if(n==0 || w==0)
        return 0;
    if(t[n][w]!=-1)
        return t[n][w];                                                 /*Dynamic Programming comes into play*/

    if (wt[n - 1] <= w)
        return t[n][w]= max((val[n - 1] + knapsack( wt, val, w - wt[n - 1], n - 1)),knapsack(wt, val, w, n - 1));     
    else 
        return t[n][w]= max((val[n - 1] + knapsack( wt, val, w - wt[n - 1], n - 1)),knapsack(wt, val, w, n - 1));     

    return t[n][w];      
}


int main()
{
    int val[] = { 60, 100, 180 };
    int wt[] = { 10, 20, 30 };
    int w = 50;
    int n = sizeof(val) / sizeof(val[0]);
    memset(t, -1, sizeof(t));
    cout << knapsack(wt, val, w, n);
    return 0;
}
