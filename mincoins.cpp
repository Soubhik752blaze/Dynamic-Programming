/*Coin Change Problem Minimum Numbers of coins
We are given a target sum of ‘X’ and ‘N’ distinct numbers denoting the coin denominations.
We need to tell the minimum number of coins required to reach the target sum.
We can pick a coin denomination for any number of times we want.*/
#include <bits/stdc++.h>
using namespace std;

int recursive()
{
    //base case


    //explore all posibilites
    
}

int minimumElements(vector<int> &arr, int target)
{
    int n = arr.size();
    int ans = recursive(n - 1, arr, target);
    return ans;
}
int main()
{
    vector<int> arr = {1, 2, 3};
    int target = 7;

    cout << "The minimum number of coins required to form the target sum is " << minimumElements(arr target);
    return 0;
}