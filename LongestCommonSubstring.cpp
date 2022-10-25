/* Question -
Given two sequences, print longest substring present in both of them.
A substring is a sequence that appears in a string in a contagious order

For example, “ab”,  “bc”, “abc”, “a”, "b", "c" .. etc are subsequences of “abc”. */
#include <bits/stdc++.h>
using namespace std;

// tabulation code is similar as that of LCS(subsequence) so we directly use it by making some modifications in logic.
// Here, the only difference is the substring is contagious in nature so in a non match case we directly return 0 and not of max of 2 choices as done in LCS.
// making the dp cell 0 incase of a mismatch is useful since it prevents increase of length of substring if there is a disruption of match in between.
// Thus, the count (here dp cell) gets restarted to 0 length.
// we maintain a "ans" variable where we keep track of max length so far
int tabulation(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();
    int ans = 0;
    // since base case has condition < 0, thus we create a dp matrix of (n+1)* (m+1)
    // and for index i and j, we take i-1 and j-1th index of strings s1 and s2
    // so for i==0, since there is no string index -1 so for for i=0 we populate dp cells with 0.. same for j==0
    // we take a max variable here to store max length of largest substring
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // base case(i==0 cells and j==0 cells) is already thus taken care of
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    ans = max(ans, dp[i][j]);
                }
            else
                dp[i][j] = 0;
        }  
    }

    return ans;
}

int spaceoptimisation(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();
    int ans = 0;
    vector<int> prev(m + 1, 0), curr(m + 1, 0);
    for (int ind1 = 1; ind1 <= n; ind1++)
    {
        for (int ind2 = 1; ind2 <= m; ind2++)
        {
            if (s1[ind1 - 1] == s2[ind2 - 1])
                {
                    curr[ind2] = 1 + prev[ind2 - 1];
                    ans = max(ans, curr[ind2]);
                }
            else
                curr[ind2] = 0;
        }
        prev = curr;
    }
    return ans;
}

int lengthofLCS(string s1, string s2)
{
    int n = s1.length();
    int m = s2.length();
    int ans = tabulation(s1, s2);
    return ans;
}
int main()
{
    string s1 = "cbadfe";
    string s2 = "afcbde";

    cout << "Length of Longest Common Substring is " << lengthofLCS(s1, s2);
    return 0;
}

// TC -> O(N*M) + O(N+M)
// SC -> O(N*M)