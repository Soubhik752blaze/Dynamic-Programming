/*Question :- Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

1. Insert a character
2. Delete a character
3. Replace a character*/

#include <bits/stdc++.h>
using namespace std;

// this function give the min no of operations needed to make string s1[ 0 to i] be exactly like s2[ 0 to j]
int recursive(int i, int j, string s1, string s2)
{
    // base case :- if any of the string is over, we need to insert more (if s1 is over) j + 1 more characters/ delete (if s2 is over ) more i + 1 characters
    if (i < 0)
        return j + 1;
    if (j < 0)
        return i + 1;

    // explore all possibilites and return best fit option
    // matching case :- we dont do any operation and move i-1,j-1 respectively in s1 and s2
    if (s1[i] == s2[j])
        return 0 + recursive(i - 1, j - 1, s1, s2);
    // non matching case :- we have 3 possible operations . we explore all of them and return the one with min no of operations needed in the end.
    //  a> Insertion :- we insert matching character of s2 in s1 at i+1 position. Then continue our search at i and j-1 positions.
    //  b> Deletion :- we delete current character of s1 and look at i-1 position. Thus, we continue our search at i-1 and j position.
    //  c> Replace :- we replace the current character of s1 with s2[j] charcter and then, continie our search with i-1 and j - 1 position.
    else
    {
        int insertion = 1 + recursive(i, j - 1, s1, s2);
        int deletion = 1 + recursive(i - 1, j, s1, s2);
        int replacement = 1 + recursive(i - 1, j - 1, s1, s2);

        return min(insertion, min(deletion, replacement));
    }
}

int memoization(int i, int j, string s1, string s2, vector<vector<int>> &dp)
{
    if (i < 0)
        return j + 1;
    if (j < 0)
        return i + 1;

    if (s1[i] == s2[j])
        return dp[i][j] = 0 + recursive(i - 1, j - 1, s1, s2);
    else
    {
        int insertion = 1 + recursive(i, j - 1, s1, s2);
        int deletion = 1 + recursive(i - 1, j, s1, s2);
        int replacement = 1 + recursive(i - 1, j - 1, s1, s2);

        return dp[i][j] = min(insertion, min(deletion, replacement));
    }
}

int tabulation(string s1, string s2)
{
    int n = s1.length();
    int m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // base case formulation
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int j = 0; j <= m; j++)
        dp[0][j] = j;

    // explore all possibilities
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = 0 + dp[i - 1][j - 1];
            else
            {
                int insertion = 1 + dp[i][j - 1];
                int deletion = 1 + dp[i - 1][j];
                int replacement = 1 + dp[i - 1][j - 1];

                dp[i][j] = min(insertion, min(deletion, replacement));
            }
        }
    return dp[n][m];
}

int spaceoptimisation(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    // base case formulation
    for (int j = 1; j <= m; j++)
        prev[j] = j;

    // explore all possibilities
    for (int i = 1; i <= n; i++)
    {
        curr[0] = i;
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                curr[j] = 0 + prev[j - 1];
            else
            {
                int insertion = 1 + curr[j - 1];
                int deletion = 1 + prev[j];
                int replacement = 1 + prev[j - 1];

                curr[j] = min(insertion, min(deletion, replacement));
            }
        }
        prev = curr;
    }
    return prev[m];
}
int minsteps(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();
    // vector<vector<int>> dp(n, vector<int>(m, -1));
    // int ans = memoization(n - 1, m - 1, s1, s2, dp);
    int ans = spaceoptimisation(s1, s2);
    return ans;
}
int main()
{
    string word1 = "horse";
    string word2 = "ros";

    cout << "Minimum number of operations required :- " << minsteps(word1, word2);
    return 0;
}

// One of the most critical and logic requiring Questions
// Leetcode Hard
// TC -> O(N*M)
// SC -> O(N*M) or O(M)