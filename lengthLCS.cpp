/* Question -
Given two sequences, print longest subsequence present in both of them.
A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous.

For example, “abc”,  “abg”, “bdf”, “aeg”,  ‘”acefg”, .. etc are subsequences of “abcdefg”. */

#include <bits/stdc++.h>
using namespace std;

// we find the dp array and length of LCS
// We use the DP array itself to find the LCS and then store it in a string
// in dp array, we check from [n][m] to [0][0] direction
// we check if s1[i] == s2[j] i.e same character check, if we yes we store it at last place of resultant string and reduce last place index by 1
// then we i-1,j-1 position
// incase the match condition is not satisfied we go dp[1-1][j] or dp[i][j-1] whichever is greater and then again check for same character
string tabulation(string s1, string s2)
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

    int length = dp[n][m];
    string ans = "";
    for (int ind = 0; ind < length; ind++)
        ans += "$";
    int ind = length - 1;

    int i = n, j = m;
    while(i>0 && j>0)
    {
        if(s1[i-1] == s2[j-1])
            {
                ans[ind] = s1[i-1];
                ind--;
                i--,j--;
            }
        else if(dp[i-1][j] > dp[i][j-1])
        {
            i--;
        }
        else{
            j--;
        }
    }
    return ans;
}

string printLCS(string s1, string s2)
{
    int n = s1.length();
    int m = s1.length();
    string ans = tabulation(s1, s2);
    return ans;
}
int main()
{
    string s1 = "abcdef";
    string s2 = "afcbde";

    cout << "Length of LCS is " << printLCS(s1, s2);
    return 0;
}

// TC -> O(N*M) + O(N+M)
// SC -> O(N*M)