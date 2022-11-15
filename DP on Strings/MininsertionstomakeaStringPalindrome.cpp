/*Question :- Given a string s. In one step you can insert any character at any index of the string.
Return the minimum number of steps to make s palindrome.
A Palindrome String is one that reads the same backward as well as forward.*/

// intution:- we need to keep the max length palindromic subsequence intact and add the rest no of characters to make the whole string a palindrome
// Thus, the entire problem boils down to find longest palindromic subsequence (LPS) length finding problem
// the answer will thus be length of string - length of LPS
#include <bits/stdc++.h>
using namespace std;

int minInsertions(string s1)
{
    int n = s1.length();
    string s2 = s1;
    reverse(s2.begin(), s2.end());
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }

    return n - dp[n][n];
}

int main()
{
    string s = "leetcode";
    cout << "Minimum number of steps to make the string palindrome is " << minInsertions(s);
}

// TC -> O(n*n)
// SC -> O(n*n)
// where n is length of string
