/*Question:- Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).*/

#include <bits/stdc++.h>
using namespace std;

// function to check if all remaining characters in string p are '*'
bool hasallstars(string p, int j)
{
    for (int i = 0; i <= j; i++)
        if (p[i] != '*')
            return false;
    return true;
}
// this function give the ans of pattern matching for string s[ 0 to i] and p[ 0 to j]
bool recursive(int i, int j, string s, string p)
{
    // base case
    // if both strings are exhausted, return true
    if (i < 0 && j < 0)
        return true;
    // if s is not exhausted but p is, then return false
    if (j < 0 && i >= 0)
        return false;
    // if s is exhausted, all remaining characters of p must be 'x'
    if (i < 0)
    {
        return hasallstars(p, j);
    }

    // explore all possibilites and return best fit option
    // match case by '?' or direct character match
    if ((s[i] == p[j]) || (p[j] == '?'))
        return recursive(i - 1, j - 1, s, p);
    // match case by '*' and not-match case
    else
    {
        if (p[j] == '*')
            return recursive(i - 1, j, s, p) || recursive(i, j - 1, s, p);
        else
            return false;
    }
}

bool memoization(int i, int j, string s, string p, vector<vector<int>> &dp)
{
    if (i < 0 && j < 0)
        return true;
    // if s is not exhausted but p is, then return false
    if (j < 0 && i >= 0)
        return false;
    // if s is exhausted, all remaining characters of p must be 'x'
    if (i < 0)
    {
        return hasallstars(p, j);
    }
    if (dp[i][j] != -1)
        return dp[i][j];
    // explore all possibilites and return best fit option
    // match case by '?' or direct character match
    if ((s[i] == p[j]) || (p[j] == '?'))
        return dp[i][j] = memoization(i - 1, j - 1, s, p, dp);
    // match case by '*' and not-match case
    else
    {
        if (p[j] == '*')
            return dp[i][j] = memoization(i - 1, j, s, p, dp) || memoization(i, j - 1, s, p, dp);
        else
            return dp[i][j] = false;
    }
}

bool tabulation(string s, string p)
{
    int n = s.size();
    int m = p.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    // base cases
    dp[0][0] = true;
    for (int j = 1; j <= m; j++)
        if (hasallstars(p, j - 1))
            dp[0][j] = true;

    // explore all possible scenarios
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if ((s[i - 1] == p[j - 1]) || (p[j - 1] == '?'))
                dp[i][j] = dp[i - 1][j - 1];
            // match case by '*' and not-match case
            else
            {
                if (p[j - 1] == '*')
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                else
                    dp[i][j] = false;
            }
        }

    return dp[n][m];
}

bool spaceoptimisation(string s, string p)
{
    int n = s.size();
    int m = p.size();
    vector<bool> prev(m + 1, false), curr(m + 1, false);

    // base cases
    prev[0] = true;
    for (int j = 1; j <= m; j++)
        if (hasallstars(p, j - 1))
            prev[j] = true;

    // explore all possible scenarios
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if ((s[i - 1] == p[j - 1]) || (p[j - 1] == '?'))
                curr[j] = prev[j - 1];
            // match case by '*' and not-match case
            else
            {
                if (p[j - 1] == '*')
                    curr[j] = prev[j] || curr[j - 1];
                else
                    curr[j] = false;
            }
        }
        prev = curr;
    }

    return prev[m];
}
bool wildcardmatch(string s, string p)
{
    int n = s.size();
    int m = p.size();
    //vector<vector<int>> dp(n, vector<int>(m, -1));
    //bool ans = memoization(n - 1, m - 1, s, p, dp);
    bool ans = spaceoptimisation(s,p);
    return ans;
}
int main()
{
    string s = "aaaef";
    string p = "a*ef";
    string ans = wildcardmatch(s, p) ? "Yes" : "No";
    cout << "Is pattern a match ? Ans:- " << ans;
}

// Leetcode hard -> needs good logical thinking
// TC -> O(N*M)
// SC -> O(N*M) or O(M)