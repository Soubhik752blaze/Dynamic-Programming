/*Question:- Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences i.e the shortest common supersequence (SCSS)
If there are multiple valid strings, return any of them.

A string s is a subsequence of string t if deleting some number of characters from t (possibly 0) results in the string s.*/

// Observations :- Common characters has to be taken only once in the SCSS. Common chacters all = LCS.
// Thus length of shortest common supersequence = n + m - LCS
// Also, from DP table, we can find out SCSS by taking all characters which we dont choose (on character mismatch) based on max value in dp[i-1][j] or dp[i][j-1]. 
// Note:- we start the process from dp[n][m] and end at i == 0 or j ==0
// for common match of characters, we obviously take it in ans string and move i--,j--
// in the end we reverse our string to get the resultant string.
#include <bits/stdc++.h>
using namespace std;

string shortestcommonsupersequence(string s1, string s2)
{
    int n = s1.length();
    int m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    //compute LCS dp table
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }

    int i = n, j = m;
    string ans = "";
    //use dp table to find SCSS
    while(i > 0 && j > 0)
    {
        if(s1[i-1] == s2[j-1])
            {
                ans.push_back(s1[i-1]);
                i--,j--;
            } 
        else if(dp[i-1][j] > dp[i][j-1])
            {
                ans.push_back(s1[i-1]);
                i--;
            }
        else{
                ans.push_back(s2[j-1]);
                j--;
            }
    }

    //remaining characters if any
    while(i>0)
        {
            ans.push_back(s1[i-1]);
            i--;
        }
    while(j>0)
        {
            ans.push_back(s2[j-1]);
            j--;
        }
    // reverse the string to get the resultant string
    reverse(ans.begin(), ans.end());
    return ans;
}
int main()
{
    string s1 = "brute";
    string s2 = "groot";

    cout << "Shortest Common Supersequence is " << shortestcommonsupersequence(s1, s2);
    return 0;
}

// TC -> O(m*n)
// SC -> O(m*n)
// Best video for this explanation:- https://www.youtube.com/watch?v=xElxAuBcvsU&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=32