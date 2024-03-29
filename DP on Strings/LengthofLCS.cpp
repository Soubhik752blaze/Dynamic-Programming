/* Question -
Given two sequences, find the length of longest subsequence present in both of them.
A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous.

For example, “abc”,  “abg”, “bdf”, “aeg”,  ‘”acefg”, .. etc are subsequences of “abcdefg”. */

#include <bits/stdc++.h>
using namespace std;

// intuition is we have to generate all cases and check for LCS "max" length, but we need to have recursion do it for us.
//  for LCS checking, we do a character wise check for every character from last to 0th index for both strings.
//  choice 1:- if two characters match, lcs length = 1 + look for lcs length in both strings excluding those characters which we verified.
//  choice 2:- if two characters dont match, we go one index down (for lookout) of 1 string and again carry on the process of checking character wise for both strings.
//  in choice 2, we make 2 choices i.e for each string we reduce index for lookout and then try to match for LCS. whichever way, we find the largest length of LCS, we return it.
int recursive(int i, int j, string s1, string s2)
{
    // base case
    if (i < 0 || j < 0)
        return 0;
    // trying out all possibilites
    // match case
    if (s1[i] == s2[j])
        return 1 + recursive(i - 1, j - 1, s1, s2);
    // not match case
    else
        return max(recursive(i, j - 1, s1, s2), recursive(i - 1, j, s1, s2));
}

int tabulation(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();

    // since base case has condition < 0, thus we create a dp matrix of (n+1)* (m+1)
    // and for index i and j, we take i-1 and j-1th index of strings s1 and s2
    // so for i==0, since there is no string index -1 so for for i=0 we populate dp cells with 0.. same for j==0
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // base case(i==0 cells and j==0 cells) is already thus taken care of
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = 0 + max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[n][m];
}

int spaceoptimisation(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();

    vector<int> prev(m + 1, 0), curr(m + 1, 0);
    for (int ind1 = 1; ind1 <= n; ind1++)
    {
        for (int ind2 = 1; ind2 <= m; ind2++)
        {
            if (s1[ind1 - 1] == s2[ind2 - 1])
                curr[ind2] = 1 + prev[ind2 - 1];
            else
                curr[ind2] = max(prev[ind2], curr[ind2 - 1]);
        }
        prev = curr;
    }

    return prev[m];
}

int lengthlcs(string s1, string s2)
{
    int n = s1.length();
    int m = s2.length();
    int ans = spaceoptimisation(s1, s2);
    return ans;
}
int main()
{
    string s1 = "abcdef";
    string s2 = "afcbde";

    cout << "Length of LCS is " << lengthlcs(s1, s2);
    return 0;
}

// TC -> O(m*n)
// SC -> O(m*n)