/*Question :- Given an expression, A, with operands and operators (OR , AND , XOR),
in how many ways can you evaluate the expression to true, by grouping in different ways?

Operands are only true and false.*/


//VIDEO LINK FOR EXPLANATION :- https://www.youtube.com/watch?v=MM7fXopgyjw&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=53
#include <bits/stdc++.h>
using namespace std;

// observations:- Operands (k) start at i + 1 end at j - 1 at an increment of +2
// for OR, we have true if T|T or T|F or T|F and false for F|F
// for AND, we have true if T&T else false for all other cases
// for XOR, we have true for T^F or F^T and false for T^T or F^F.
// we take total count of true and false ways because for True ways also, we are dependent on some false ways as well as seen above
// for base case we have individual characters so we check if we are checking for that character or not, if yes we return 1 else 0
int recursive(int i, int j, int istrue, string exp)
{
    // base case
    if (i > j)
        return 0;
    if (i == j)
    {
        // if we are looking for true, equate to T else to F
        if (istrue)
            return exp[i] == 'T';
        else
            return exp[i] == 'F';
    }
    // explore all possibilites
    int count = 0;
    for (int k = i + 1; k < j; k += 2)
    {
        int lt = recursive(i, k - 1, 1, exp);
        int lf = recursive(i, k - 1, 0, exp);
        int rt = recursive(k + 1, j, 1, exp);
        int rf = recursive(k + 1, j, 0, exp);
        // for OR (|) case
        if (exp[k] == '|')
        {
            if (istrue)
                count += (lt * rf) + (lf * rt) + (lt * rt);
            else
                count += (lf * rf);
        }
        // for AND (&) case
        else if (exp[k] == '&')
        {
            if (istrue)
                count += lt * rt;
            else
                count += (lt * rf) + (lf * rt) + (lf * rf);
        }
        // for XOR (^) case
        else if (exp[k] == '^')
        {
            if (istrue)
                count += (lt * rf) + (lf * rt);
            else
                count += (lt * rt) + (lf * rf);
        }
    }
    // return statement
    return count;
}

int memoization(int i, int j, int istrue, string exp, vector<vector<vector<int>>> &dp)
{
    // base case
    if (i > j)
        return 0;
    if (i == j)
    {
        // if we are looking for true, equate to T else to F
        if (istrue)
            return exp[i] == 'T';
        else
            return exp[i] == 'F';
    }
    if (dp[i][j][istrue] != -1)
        return dp[i][j][istrue];
    // explore all possibilites
    int count = 0;
    for (int k = i + 1; k < j; k += 2)
    {
        int lt = memoization(i, k - 1, 1, exp, dp);
        int lf = memoization(i, k - 1, 0, exp, dp);
        int rt = memoization(k + 1, j, 1, exp, dp);
        int rf = memoization(k + 1, j, 0, exp, dp);
        // for OR (|) case
        if (exp[k] == '|')
        {
            if (istrue)
                count += (lt * rf) + (lf * rt) + (lt * rt);
            else
                count += (lf * rf);
        }
        // for AND (&) case
        else if (exp[k] == '&')
        {
            if (istrue)
                count += lt * rt;
            else
                count += (lt * rf) + (lf * rt) + (lf * rf);
        }
        // for XOR (^) case
        else if (exp[k] == '^')
        {
            if (istrue)
                count += (lt * rf) + (lf * rt);
            else
                count += (lt * rt) + (lf * rf);
        }
    }
    // return statement
    return dp[i][j][istrue] = count;
}

int tabulation(string exp)
{
    int n = exp.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));
    // base case
    for (int i = 0; i < n; i++)
    {
        dp[i][i][1] = (exp[i] == 'T');
        dp[i][i][0] = (exp[i] == 'F');
    }
    // express interms of loop
    for (int i = n - 1; i >= 0; i--)
        for (int j = i + 1; j <= n - 1; j++)
            for (int istrue = 0; istrue <= 1; istrue++)
            {
                int count = 0;
                for (int k = i + 1; k < j; k += 2)
                {
                    int lt = dp[i][k - 1][1];
                    int lf = dp[i][k - 1][0];
                    int rt = dp[k + 1][j][1];
                    int rf = dp[k + 1][j][0];
                    // for OR (|) case
                    if (exp[k] == '|')
                    {
                        if (istrue)
                            count += (lt * rf) + (lf * rt) + (lt * rt);
                        else
                            count += (lf * rf);
                    }
                    // for AND (&) case
                    else if (exp[k] == '&')
                    {
                        if (istrue)
                            count += (lt * rt);
                        else
                            count += (lt * rf) + (lf * rt) + (lf * rf);
                    }
                    // for XOR (^) case
                    else if (exp[k] == '^')
                    {
                        if (istrue)
                            count += (lt * rf) + (lf * rt);
                        else
                            count += (lt * rt) + (lf * rf);
                    }
                }
                dp[i][j][istrue] = count;
            }
    // return statement
    return dp[0][n - 1][1];
}
int evaluateexpression(string exp)
{
    int n = exp.size();
    // vector<vector<vector<int>>> dp(n,vector<vector<int>> (n, vector<int> (2, -1)));
    // int ans = memoization(0, n - 1, 1, exp, dp);
    int ans = tabulation(exp);
    return ans;
}

int main()
{
    string exp = "T|F&F&T";
    cout << "Max no of ways the expression results to true is " << evaluateexpression(exp);
}

// Hardest Question ( interms of logical thinking ) in Partition DP
// TC -> O(n*n*2) * O(n) = o(n^3)
// SC -> O(n*n*2)