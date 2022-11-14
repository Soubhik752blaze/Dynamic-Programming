/*Question:- Given two strings s and t, return the number of distinct subsequences of s which equals t.*/

#include <bits/stdc++.h>
using namespace std;

// We have to find distinct subsequences of S2 in S1. As there is no uniformity in data, there is no other way to find out than to try out all possible ways and hence use recursion.
// now again like lcs, here there will be matching and non matching scenarios but here we cant return 1 on a match since we need to check that the entire subsequence is present only then we can return 1 for a valid count.
// thus, here we return 1 and 0 only in base cases
// for non-matching scenario, we go one index down in string 's' and continue the search
// for matching scenario, there are 2 possible scenarios :-
// 1. we can have the match as a part of search, and go 1 index down on both "s" and "t".
// 2. we can ignore this matched character and go down the index only on "s" for any other subsequence match.
// Since, we are counting ways in total, we take summation of all choices
int recursive(int i, int j, string s, string t)
{
    // base case
    if (j < 0)
        return 1;
    if (i < 0)
        return 0;

    // explore all possibilites and calculate them, then find the best option and return it
    // matching case
    if (s[i] == t[j])
        return recursive(i - 1, j - 1, s, t) + recursive(i - 1, j, s, t);
    // non-matching case
    else
        return recursive(i - 1, j, s, t);
}

int memoization(int i, int j, string s, string t, vector<vector<int>> dp)
{
    // base case
    if (j < 0)
        return 1;
    if (i < 0)
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    // explore all possibilites and calculate them, then find the best option and return it
    // matching case
    if (s[i] == t[j])
        return dp[i][j] = memoization(i - 1, j - 1, s, t, dp) + memoization(i - 1, j, s, t, dp);
    // non-matching case
    else
        return dp[i][j] = memoization(i - 1, j, s, t, dp);
}

int tabulation(string s, string t)
{
    int n = s.length();
    int m = t.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    //base case adjustment
    for (int j = 0; j <= m; j++)
        dp[0][j] = 0;
    for (int i = 0; i <= n; i++)
        dp[i][0] = 1;
    

    //exploring all possibilites and then returning best fit outcome
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (s[i-1] == t[j-1])
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
            else
                dp[i][j] = dp[i-1][j];
        }

    return dp[n][m];
}

int spaceoptimised(string s, string t)
{
    int n = s.length();
    int m = t.length();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    //base case adjustment
    prev[0] = curr[0] = 1;
    

    //exploring all possibilites and then returning best fit outcome
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++)
        {
            if (s[i-1] == t[j-1])
                curr[j] = prev[j-1] + prev[j];
            else
                curr[j] = prev[j];
        }
        prev = curr;
    }

    return prev[m];
}

// curr is not dependent on curr so we can implement the exact space-optimised logic using just a single array 
// also, the inner loop will run from j = m to j = 1 as it will not hamper the creation of the earlier prev[j] results ( as prev[j] = prev[j-1] + prev[j])
int _1DArrayoptimised(string s, string t)
{
    int n = s.length();
    int m = t.length();
    vector<int> prev(m + 1, 0);

    //base case adjustment
    prev[0] = 1;
    

    //exploring all possibilites and then returning best fit outcome
    for (int i = 1; i <= n; i++){
        for (int j = m; j >= 1; j--)
        {
            if (s[i-1] == t[j-1])
                prev[j] = prev[j-1] + prev[j];
        }
    }

    return prev[m];
}
int countdistinctsubsequences(string s, string t)
{
    int n = s.length();
    int m = t.length();
    // vector<vector<int>> dp( n, vector<int> (m, -1));
    int ans = _1DArrayoptimised(s, t);
    return ans;
}

int main()
{
    string s = "rabbbit";
    string t = "rabbit";

    cout << "No of distinct subsequences of s which equals t are :- " << countdistinctsubsequences(s, t);
    return 0;
}

// TC -> O(m*n)
// SC -> O(m*n)