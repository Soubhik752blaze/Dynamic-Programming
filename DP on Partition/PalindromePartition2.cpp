/*Question :- Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.

Example 1:
Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.*/

#include <bits/stdc++.h>
using namespace std;
// palindrome checker function
bool ispalindrome(string &s, int i, int j)
{
    while (i < j)
    {
        if (s[i++] != s[j--])
            return false;
    }
    return true;
}

// based on front partitioning 
// we start making partitions and for every partition, we check if the left substring is palindrome or not
// if yes, we add 1 to ans and recursive solve the right substring
// in the end, we take the minimum of the partitions required.
int recursive(int i, string &exp, int n)
{
    // base case
    if (i == n)
        return 0;
    // explore all possibilites
    int count = 1e9;
    for (int k = i; k < n; k++)
    {
        if (ispalindrome(exp, i, k))
        {
            int ways = 1 + recursive(k + 1, exp, n);
            count = min(count, ways);
        }
    }
    return count;
}

int memoization(int i, string &exp, int n, vector<int> &dp)
{
    // base case
    if (i == n)
        return 0;
    if (dp[i] != -1)
        return dp[i];
    // explore all possibilites
    int count = 1e9;
    for (int k = i; k < n; k++)
    {
        if (ispalindrome(exp, i, k))
        {
            int ways = 1 + memoization(k + 1, exp, n, dp);
            count = min(count, ways);
        }
    }
    return dp[i] = count;
}

int tabulation(string exp, int n)
{
    vector<int> dp(n + 1, 0);
    // base case already taken care
    // express general scenarios in terms of loops
    for (int i = n - 1; i >= 0; i--)
    {
        int count = 1e9;
        for (int k = i; k < n; k++)
        {
            if (ispalindrome(exp, i, k))
            {
                int ways = 1 + dp[k + 1];
                count = min(count, ways);
            }
        }
        dp[i] = count;
    }
    // return statement
    return dp[0];
}
int palindromepartition(string exp)
{
    int n = exp.size();
    // vector<int> dp(n, -1);
    // int ans = memoization(0, exp, n, dp);
    int ans = tabulation(exp, n);
    //-1 for making partition at end which doesnot count
    return ans - 1;
}

int main()
{
    string exp = "aab";
    cout << "Min no of partitions needed are :- \n " << palindromepartition(exp);
}

// Example of front partition problem -> somewhat like palindrome partition 1 (recursion playlist striver)
// TC -> O(n*n) * o(n/2) for checking palindrome so approximately o(n^3)
// SC -> O(n)