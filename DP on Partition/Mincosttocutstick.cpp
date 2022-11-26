/*Question :- Given a wooden stick of length n units. The stick is labelled from 0 to n. like( 0 to 1, 1 to 2, 2 to 3, 3 to 4, 4 to n)
Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.
You should perform the cuts in order, you can change the order of the cuts as you wish.

The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of all cuts. When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their lengths is the length of the stick before the cut). Please refer to the first example for a better explanation.
Return the minimum total cost of the cuts.*/

#include <bits/stdc++.h>
using namespace std;

// for this problem, best is to understand via video explanation by striver :- https://www.youtube.com/watch?v=xwomavsC86c&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=51
int recursive(int i, int j, vector<int> cuts)
{
    // base case
    if (i > j)
        return 0;
    // try all possibilities
    int mini = INT_MAX;
    for (int k = i; k <= j; k++)
    {
        int cost = (cuts[j + 1] - cuts[i - 1]) + recursive(i, k - 1, cuts) + recursive(k + 1, j, cuts);
        mini = min(cost, mini);
    }
    // return statement
    return mini;
}

int memoization(int i, int j, vector<int> cuts, vector<vector<int>> &dp)
{
    // base case
    if (i > j)
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    // try all possibilities
    int mini = INT_MAX;
    for (int k = i; k <= j; k++)
    {
        int cost = (cuts[j + 1] - cuts[i - 1]) + memoization(i, k - 1, cuts, dp) + memoization(k + 1, j, cuts, dp);
        mini = min(cost, mini);
    }
    // return statement
    return dp[i][j] = mini;
}

int tabulation(vector<int> cuts, int n)
{
    int c = cuts.size();
    vector<vector<int>> dp(c, vector<int>(c, 0));
    // write all possibilites in terms of indexes and loop
    for (int i = c - 2; i >= 1; i--)
        for (int j = 1; j <= c - 2; j++)
        {
            //base case
            if( i > j)  
                continue;
            int mini = INT_MAX;
            for (int k = i; k <= j; k++)
            {
                int cost = (cuts[j + 1] - cuts[i - 1]) + dp[i][k - 1] + dp[k + 1][j];
                mini = min(cost, mini);
            }
            dp[i][j] = mini;
        }
    // return statment
    return dp[1][c - 2];
}
int mincosttocutstick(int n, vector<int> cuts)
{
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    // int c = cuts.size();
    // vector<vector<int>> dp(c, vector<int>(c, -1));
    // int ans = memoization(1, c - 2, cuts, dp);
    int ans = tabulation(cuts, n);
    return ans;
}

int main()
{
    vector<int> cuts = {1, 3, 4, 5};
    int n = 7;
    cout << "Minimum cost of cuts is " << mincosttocutstick(n, cuts);
}

// Hard to Intuitively find the answer
// sort of a pattern to keep in mind
// TC -> O(N*N*N)
// SC -> O(N*N)