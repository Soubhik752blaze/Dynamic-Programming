/* Question:- Given a string "S", we need to print the length of the longest palindromic subsequence.
A palindromic string is a string that is equal to its reverse. For example: “nitin” is a palindromic string.*/

#include <bits/stdc++.h>
using namespace std;

// intuition is the LPS has 2 properties:- its same as its reverse and its length is fixed
// thus, if we want to find the longest palindromic subsequence length, then we can just the find the length of LCS of the input string and its reverse
// The longest palindromic subsequence being a palindrome will remain the same when the entire string is reversed. ( and ofcouse LCS is the longest by itself)
// thus, we simply find the LCS of the input string and its reversed string
int tabulation(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();
    
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
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
            {
                curr[ind2] = 1 + prev[ind2 - 1];
            }
            else
                curr[ind2] = 0 + max(prev[ind2], curr[ind2 - 1]);
        }
        prev = curr;
    }
    return prev[m];
}

int lengthofLPS(string s1)
{
    string s2 = s1;
    reverse(s2.begin(), s2.end());
    int n = s1.length();
    int m = s2.length();
    int ans = spaceoptimisation(s1, s2);
    return ans;
}
int main()
{
    string s = "bbabccbab";         //LPS is babcbab

    cout << "Length of Longest Palindromic subsequence is " << lengthofLPS(s);
    return 0;
}

// TC -> O(N*M)
// SC -> O(N*M)