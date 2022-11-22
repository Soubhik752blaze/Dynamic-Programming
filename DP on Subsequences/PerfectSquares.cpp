/*Question:- Given an integer n, return the least number of perfect square numbers that sum to n.

A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. */

#include <bits/stdc++.h>
using namespace std;

// variation of min coins problem
// after analysis few testcases, we will see that greedy approach doesnot work, so we have to use recursion
// in recursive function, we run a loop from i = 1 to sqrt(n), and try if n is divisible by i.
// if yes, then we divide by it (by adding 1 to ans as 1 divide took place) and run the function on the quotient until it becomes 0.
// at every step, we return the minimum choice leading us to having min of sum required at the end
int recursive(int n)
{
    // TC -> o()
    //  base case
    if (n == 0)
        return 0;
    // general expression or do all possible scenarios on n
    int ans = n; // as max n no of 1s will make sum equal to n
    for (int i = 1; i <= sqrt(n); i++)
    {
        ans = min(ans, 1 + recursive(n - i * i));
    }
    // return statement
    return ans;
}

int memoization(int n, vector<int> &dp)
{
    // base case
    if (n == 0)
        return 0;
    if (dp[n] != -1)
        return dp[n];
    // general expression or do all possible scenarios on n
    // as max n no of 1s will make sum equal to n
    int ans = n;
    for (int i = 1; i <= sqrt(n); i++)
    {
        ans = min(ans, 1 + memoization(n - i * i, dp));
    }
    return dp[n] = ans;
}

int tabulation(int n)
{
    vector<int> dp(n + 1, INT_MAX);
    // base case
    dp[0] = 0; 
    // general scenario
    for (int i = 1; i <= n; i++){
        int ans = i;
        for (int j = 1; j <= sqrt(i); j++)
        {
            ans = min(ans, 1 + dp[i - j * j]);
        }
        dp[i] = ans;
    }
    //return 
    return dp[n];
}
int perfectsquares(int n)
{
    vector<int> dp(n + 1, -1);
    int ans = tabulation(n);
    return ans;
}
int main()
{
    int n = 12;
    cout << "Min no of perfect Squares needed are " << perfectsquares(n);
}

//TC -> o(n*sqrt(n))
//SC -> o(n)