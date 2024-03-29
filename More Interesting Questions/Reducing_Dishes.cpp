/*Question :- A chef has collected data on the satisfaction level of his n dishes.
Chef can cook any dish in 1 unit of time.
Like-time coefficient of a dish is defined as the time taken to cook that dish including previous dishes multiplied by its satisfaction level i.e. time[i] * satisfaction[i].
Return the maximum sum of like-time coefficient that the chef can obtain after dishes preparation.

Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value.*/

#include <bits/stdc++.h>
using namespace std;

// Logic/Intuition :- Pattern of 0/1 knapsack just on a sorted array(either take or dont take)

// memoization
int solvebymemoization(vector<int> &satisfaction, int index, int time, vector<vector<int>> &dp)
{
    if (index == satisfaction.size())
        return 0;
    if (dp[index][time] != -1)
        return dp[index][time];
    int include = (satisfaction[index] * (time + 1)) + solvebymemoization(satisfaction, index + 1, time + 1, dp);
    int exclude = 0 + solvebymemoization(satisfaction, index + 1, time, dp);

    return dp[index][time] = max(include, exclude);
}
// tabulation
int solvebytabulation(vector<int> &satisfaction)
{
    int n = satisfaction.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = n - 1; i >= 0; i--)
        for (int j = i; j >= 0; j--)
        {
            int include = (satisfaction[i] * (j + 1)) + dp[i + 1][j + 1];
            int exclude = 0 + dp[i + 1][j];

            dp[i][j] = max(include, exclude);
        }

    return dp[0][0];
}

int maxSatisfaction(vector<int> &satisfaction)
{
    sort(satisfaction.begin(), satisfaction.end());
    return solvebytabulation(satisfaction);
}

// Non-Intuitive O(nlogn) Solution
/*The algorithm used in this solution is based on sorting the satisfaction list in descending order and iterating over it. 
At each iteration, the satisfaction of the current dish is added to a running sum "sum", and if this sum is positive, it is added to the answer varibale "ans". 
This guarantees that the algorithm always considers the best dishes to cook, which are the ones with higher satisfaction values.*/
int maxSatisfactionBestSolution(vector<int> &satisfaction)
{
    vector<int> v = satisfaction;
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    int sum = 0, ans = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (sum + v[i] > 0)
        {
            ans += sum + v[i];
            sum += v[i];
        }
    }
    return ans;
}
int main()
{
    vector<int> satisfaction = {-1, -8, 0, 5, -9};
    int ans = maxSatisfaction(satisfaction);
    cout << "Max Like Coefficient is " << ans;
    return 0;
}

// TC -> O(n*n) but can be optimised to O(nlogn) in best solution
// SC -> O(n*n) but can be optimised to O(1) in best solution