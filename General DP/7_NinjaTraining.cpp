/*Question :- A Ninja has an ‘N’ Day training schedule.
He has to perform one of these three activities (Running, Fighting Practice, or Learning New Moves) each day.
There are merit points associated with performing an activity each day.
The same activity can’t be performed on two consecutive days.
We need to find the maximum merit points the ninja can attain in N Days.

We are given a 2D Array POINTS of size ‘N*3’ which tells us the merit point of specific activity on that particular day.
Our task is to calculate the maximum number of merit points that the ninja can earn.
*/

#include <bits/stdc++.h>
using namespace std;

// Main intuition is we have a variable last which tells us that day which activity was performed
// for prev day, we avoid that activity and do the activity which is most rewarding next.
// we develop this idea recursively and then make changes for having optimisation by DP
int solvebyrecursive(vector<vector<int>> arr, int day, int last)
{
    if (day == 0)
    {
        int maxpoints = 0;
        for (int i = 0; i < 3; i++)
        {
            if (i != last)
                maxpoints = max(maxpoints, arr[day][i]);
        }
        return maxpoints;
    }
    int maxpoints = 0;
    for (int i = 0; i < 3; i++)
    {
        if (i != last)
        {
            int point = arr[day][i] + solvebyrecursive(arr, day - 1, i);
            maxpoints = max(maxpoints, point);
        }
    }
    return maxpoints;
}

int solvebyMemoization(vector<vector<int>> arr, int day, int last, vector<vector<int>> &dp)
{
    if (dp[day][last] != -1)
        return dp[day][last];
    if (day == 0)
    {
        int maxpoint = 0;
        for (int i = 0; i < 3; i++)
        {
            if (i != last)
                maxpoint = max(maxpoint, arr[day][i]);
        }
        return dp[day][last] = maxpoint;
    }

    int maxpoint = 0;
    for (int i = 0; i < 3; i++)
    {
        if (i != last)
        {
            int point = arr[day][i] + solvebyMemoization(arr, day - 1, i, dp);
            maxpoint = max(maxpoint, point);
        }
    }
    return dp[day][last] = maxpoint;
}

int solvebyTabulation(vector<vector<int>> arr)
{
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(4, 0));

    // setting base conditions
    // dp[0][0] = max(arr[0][1], arr[0][2]);
    // dp[0][1] = max(arr[0][0], arr[0][2]);
    // dp[0][2] = max(arr[0][0], arr[0][1]);
    // dp[0][3] = max(arr[0][0], max(arr[0][1], arr[0][2]));

    for (int task = 0; task < 4; task++){
        int maxpoint = 0;
        for (int last = 0; last < 3; last++){
            if (last != task){
                maxpoint = max(maxpoint, arr[0][last]);
            } 
        }
        dp[0][task] = maxpoint;
    }
        
    // dp calculation
    for (int day = 1; day < n; day++)
        for (int last = 0; last < 4; last++){
            dp[day][last] = 0;
            for (int i = 0; i < 3; i++){
                if (i != last){
                    int point = arr[day][i] + dp[day - 1][i];
                    dp[day][last] = max(dp[day][last], point);
                }
            }
        }
    return dp[n - 1][3];
}

int optimisedDP(vector<vector<int>> arr)
{
    int n = arr.size();
    vector<int> prev(4, 0);
    // setting base conditions
    prev[0] = max(arr[0][1], arr[0][2]);
    prev[1] = max(arr[0][0], arr[0][2]);
    prev[2] = max(arr[0][0], arr[0][1]);
    prev[3] = max(arr[0][0], max(arr[0][1], arr[0][2]));
    // dp calculation
    for (int day = 1; day < n; day++)
    {
        vector<int> temp(4, 0);
        for (int last = 0; last < 4; last++)
        {
            temp[last] = 0;
            for (int i = 0; i < 3; i++)
            {
                if (i != last)
                {
                    int point = arr[day][i] + prev[i];
                    temp[last] = max(temp[last], point);
                }
            }
        }
        prev = temp;
    }
    return prev[3];
}

int ninjatraining(vector<vector<int>> arr)
{
    int n = arr.size();
    // int ans = solvebyrecursive(arr, n - 1, 3);
    // vector<vector<int>> dp (n, vector<int> (4, -1));
    // int ans = solvebyMemoization(arr, n - 1, 3, dp);
    int ans = solvebyTabulation(arr);
    // int ans = optimisedDP(arr);
    return ans;
}
int main()
{
    vector<vector<int>> arr = {{10, 40, 70},
                               {20, 50, 80},
                               {30, 60, 90}};
    cout << ninjatraining(arr);
}
/* 2D DP problem
Time Complexity: O(N*4*3)
Reason: There are three nested loops

Space Complexity: O(1) best case
*/