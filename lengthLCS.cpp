/* Question - Longest Common Subsequence Problem solution using recursion
Given two sequences, find the length of longest subsequence present in both of them.
A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous. 

For example, “abc”,  “abg”, “bdf”, “aeg”,  ‘”acefg”, .. etc are subsequences of “abcdefg”. */

#include <bits/stdc++.h>
using namespace std;


/*DP SOLUTION*/
int length_lcs(char *x,char *y, int n, int m)
{
    int t[n+1][m+1];
    for (int i = 0; i < n+1; i++)
    {    for (int j = 0; j < m+1; j++)
        {
            if ( i == 0 || j == 0)
                t[i][j] = 0;
            else if (x[i-1] == y[j-1])
                t[i][j] = 1 + t[i-1][j-1];
            else 
                t[i][j] = max( t[i-1][j], t[i][j-1]);
        }
    }           
    return t[n][m];
}

int main()
{
char seq1[] = "AGGTAB";
char seq2[] = "GXTXAYB";
int n = strlen(seq1);
int m = strlen(seq2);

cout<<"Length of LCS is "<<length_lcs(seq1,seq2,n,m);
return 0;
}