/*Question:- Given two strings str1 and str2. 
The task is to remove or insert the minimum number of characters from/in str1 so as to transform it into str2. 
It could be possible that the same character needs to be removed/deleted from one point of str1 and inserted to some another point.*/

#include<bits/stdc++.h>
using namespace std;

// Intuition:- Find the LCS length and since the rest of the characters dont match, so we need to first remove the characters from str 1 and add the ones in str2.
// So, Ans :- n + m - (2*lcs) where n and m are lengths of the strings str1 and str2 respectively
int minDistance(string s1, string s2) {
        int n = s1.size();
        int m = s2.size();


        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
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
        int lcs = dp[n][m];
        return n + m - (2*lcs);
    }

int main()
{
    string a = "kite";
    string b = "mice";
    cout << "Minimum number of steps to make the string palindrome is " << minDistance(a,b);
}

// TC -> O(n*m)
// SC -> O(n*m)