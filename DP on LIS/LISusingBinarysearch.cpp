/*Question :- Given an integer array nums, return the length of the longest strictly increasing subsequence.
The longest increasing subsequence is described as a subsequence of an array where:
    All elements of the subsequence are in increasing order.
    This subsequence itself is of the longest length possible.*/

// In questions where DP solutions give TLE, we can use Binary search for reduced time complexity
// This solution covers the binary search approach to solving the LIS problem
#include <bits/stdc++.h>
using namespace std;

// Best Explanation for this Problem including thought process :- https://takeuforward.org/data-structure/longest-increasing-subsequence-binary-search-dp-43/
// Attaching Link because explaining this problem with comments wont be as beneficial as reading the article itself
int lengthofLIS(vector<int> arr)
{

    int n = arr.size();
    vector<int> temp;
    temp.push_back(arr[0]);
    int len = 1;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > temp.back())
        {
            // arr[i] > the last element of temp array
            // so arr[i] gets appended to the last of the array temp and length of array increases by 1
            temp.push_back(arr[i]);
            len++;
        }
        else
        {
            // replacement step
            int ind = lower_bound(temp.begin(), temp.end(), arr[i]) - temp.begin();
            temp[ind] = arr[i];
        }
    }

    return len;
}

int main()
{
    vector<int> nums = {5, 4, 11, 1, 16, 8};
    cout << "Length of LIS is :- " << lengthofLIS(nums);
}

// TC -> O(n*logn)
// SC -> O(n)
