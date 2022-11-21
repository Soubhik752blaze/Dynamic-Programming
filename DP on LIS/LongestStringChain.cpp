/*Question :- You are given an array of words where each word consists of lowercase English letters.

wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.

For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on.
A single word is trivially a word chain with k == 1.

Return the length of the longest possible word chain with words chosen from the given list of words.*/

#include <bits/stdc++.h>
using namespace std;

// comparator functions
bool cmp(string a, string b)
{
    if (a.size() >= b.size())
        return false;
    return true;
}
bool checkifpossible(string next, string prev)
{
    int n = next.size();
    int m = prev.size();
    if (n - m != 1)
        return false;
    int i = 0, j = 0;
    while (i != n)
    {
        if (next[i] == prev[j])
        {
            i++;
            j++;
        }
        else
            i++;
    }
    if (i == n && j == m)
        return true;
    return false;
}
// we can convert this question to LIS if instead of LIS we consider here longest String subsequence..
// in LIS, each next element had to be greater than prev one and here next string must be greater than the last string by 1
// Thus intuition :- using LIS logic, it shoule be possible to solve this question as well
int LongestStringChain(vector<string> &str)
{
    sort(str.begin(), str.end(), cmp);
    int n = str.size();
    vector<int> dp(n, 1);
    int max_length = 1;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (checkifpossible(str[i], str[j]) && dp[i] < 1 + dp[j])
                dp[i] = 1 + dp[j];
        }
        max_length = max(max_length, dp[i]);
    }
    return max_length;
}

int main()
{
    vector<string> str = {"abcd", "dbqca"};
    cout << "length of the longest possible word chain is " << LongestStringChain(str);
}

// TC -> O(N*N)
// SC -> O(N)
