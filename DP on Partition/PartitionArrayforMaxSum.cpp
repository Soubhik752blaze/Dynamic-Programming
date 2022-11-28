/*Question :- Given an integer array arr, partition the array into (contiguous) subarrays of length at most k.
After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning.
Example 1:

Input: arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation: arr becomes [15,15,15,9,10,10,10]*/

#include <bits/stdc++.h>
using namespace std;

// we can have multiple partitions, thats why we need to cover all possible ways thats why recursion is needed.
// for replacing the entire subarray with all max elements and taking the sum, we keep track of length of subarray and max element in that partition
// that way the sum of that partition becomes (length of partition)*(max element in that parition)
// we do this for all possible partitions and take the max possible sum out as the answer
// recursive(i) means max_sum for the vector "arr" when it is starting from index i and ending at n-1.
int recursive(int i, int k, vector<int> arr, int n)
{
    // base case
    if (i == n)
        return 0;
    // try all possibilites
    int len = 0, maxi = INT_MIN, max_sum = INT_MIN;
    // j<min(n,i+k) is for check such that j doesnot go out of array bounds
    for (int j = i; j < min(n, i + k); j++)
    {
        len++;
        maxi = max(maxi, arr[j]);
        int sum = (len * maxi) + recursive(j + 1, k, arr, n);
        max_sum = max(max_sum, sum);
    }
    // return best choice
    return max_sum;
}

int memoization(int i, int k, vector<int> arr, int n, vector<int> &dp)
{
    // base case
    if (i == n)
        return 0;
    if (dp[i] != -1)
        return dp[i];
    // try all possibilites
    int len = 0, maxi = INT_MIN, max_sum = INT_MIN;
    // j<min(n,i+k) is for check such that j doesnot go out of array bounds
    for (int j = i; j < min(n, i + k); j++)
    {
        len++;
        maxi = max(maxi, arr[j]);
        int sum = (len * maxi) + memoization(j + 1, k, arr, n, dp);
        max_sum = max(max_sum, sum);
    }
    // return best choice
    return dp[i] = max_sum;
}

int tabulation(vector<int> arr, int k)
{
    int n = arr.size();
    vector<int> dp(n + 1, 0);
    // base case already taken care of
    // express all possible scenarios using loops
    for (int i = n - 1; i >= 0; i--)
    {
        int len = 0, maxi = INT_MIN, max_sum = INT_MIN;
        // j<min(n,i+k) is for check such that j doesnot go out of array bounds
        for (int j = i; j < min(n, i + k); j++)
        {
            len++;
            maxi = max(maxi, arr[j]);
            int sum = (len * maxi) + dp[j + 1];
            max_sum = max(max_sum, sum);
        }
        dp[i] = max_sum;
    }
    // return statement
    return dp[0];
}

int partitionarraymaxsum(vector<int> arr, int k)
{
    int n = arr.size();
    // vector<int> dp(n + 1, -1);
    // int ans = memoization(0, k, arr, n, dp);
    int ans = tabulation(arr, k);
    return ans;
}

int main()
{
    vector<int> arr = {1, 15, 7, 9, 2, 5, 10};
    int k = 3;
    cout << "Max Sum is " << partitionarraymaxsum(arr, k);
}

// front partition problem
// TC -> O(n*k)
// SC -> O(n)