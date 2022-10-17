/*Question :- We are given an array ‘ARR’ with N positive integers.
We need to find if we can partition the array into two subsets such that the sum of elements of each subset is equal to the other.
If we can partition, return true else return false*/

#include <bits/stdc++.h>
using namespace std;
//This question is just a modification of Subsetsum with target problem
// We just check if a subset with target = (sum of all array elements)/2 exists or not. Then the other subsets with sum/2 target will also exist
// so its just subsetsum problem with target = sum/2

bool recursive(int i, int n, vector<int> &arr, int target)
{
    // base case
    // if the target is achieved we return true or if we have reached last index, we check if target is achieved
    if (target == 0)
        return true;
    if (i == n - 1)
        return arr[i] == target;

    // traversal or calculation
    // either we pick the element in our required subsequence or we dont
    //  we pick it only if its less than the required target now
    bool taken = false;
    if (arr[i] <= target)
        taken = recursive(i + 1, n, arr, target - arr[i]);
    bool not_taken = recursive(i + 1, n, arr, target);

    // return statement
    return taken || not_taken;
}

bool memoization(int i, int n, vector<int> &arr, int target, vector<vector<int>> &dp)
{
    // base case
    // if the target is achieved we return true or if we have reached last index, we check if target is achieved
    if (target == 0)
        return true;
    if (i == n - 1)
        return arr[i] == target;
    if (dp[i][target] != -1)
        return dp[i][target];

    // traversal or calculation
    // either we pick the element in our required subsequence or we dont
    //  we pick it only if its less than the required target now
    bool taken = false;
    if (arr[i] <= target)
        taken = memoization(i + 1, n, arr, target - arr[i], dp);
    bool not_taken = memoization(i + 1, n, arr, target, dp);

    // return statement
    return dp[i][target] = (taken || not_taken);
}

bool tabulation(int n, vector<int> &arr, int k)
{
    vector<vector<bool>> dp (n, vector<bool> (k+1, false));
    //base-case
    for(int i = 0; i < n; i++)
        dp[i][0] = true;
    if(arr[0]<=k)
        dp[0][arr[0]] = true;
    
    //write for loops and do calculation
    for(int i = 1; i < n; i++)
        for(int target = 1; target <= k; target++)
        {
            bool not_taken = dp[i - 1][target];
            bool taken = false;
            if (arr[i] <= target)
                taken = dp[i - 1][target - arr[i]];

            dp[i][target] = taken || not_taken;
        }
    
    //return statement
    return dp[n-1][k];
}

bool spaceoptimised(int n, vector<int> &arr, int k)
{
    vector<bool> prev (k+1, 0), curr (k+1,0);
    //base-cases
    prev[0] = curr[0] = true;
    if(arr[0]<=k)
        prev[arr[0]] = true;
    
    //write for loops and do calculation
    for(int i = 1; i < n; i++){
        for(int target = 1; target <= k; target++)
        {
            bool not_taken = prev[target];
            bool taken = false;
            if (arr[i] <= target)
                taken = prev[target - arr[i]];

            curr[target] = taken || not_taken;
        }
    prev = curr;
    }
    //return statement
    return prev[k];
}

bool canPartition(int n, vector<int> arr)
{
    //This question is just a modification of Subsetsum with target problem
    // We just check if a subset with target = (sum of all array elements)/2 exists or not. Then the other subsets with sum/2 target will also exist
    // so its just subsetsum problem with target = sum/2
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    if (sum % 2 )
        return false;
    else
        return recursive(0, n, arr, sum / 2);
}
int main()
{

    vector<int> arr = {2, 3, 3, 3, 4, 5};
    int n = arr.size();

    if (canPartition(n, arr))
        cout << "The Array can be partitioned into two equal subsets";
    else
        cout << "The Array cannot be partitioned into two equal subsets";
}

// TC ->
// SC ->
