// Question:- Given n, find the nth fibonacci no.
#include <bits/stdc++.h>
using namespace std;

int fibonacci_tabulation(int n)
{
    // TC -> o(n), SC -> o(n)
    // storing all computed data in the dp vector to avoid recalculations each and every time
    vector<int> dp(n + 1, -1);

    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
    // returning n-1th element because we are starting from 0 index so n effectively means n-1
    return dp[n];
}

int fibonacci_optimal(int n)
{
    // TC -> o(n), SC -> o(1)

    // same as tabulation method, the only difference being we are using variables inplace of vector
    // this is because from logical pov, we only need the prev 2 values for calculation
    // so for just 2 values, its better to use 2 variables and not a vector, thus saving up a lot of space
    int curr;
    int prev = 1;
    int prev2 = 0;
    for (int i = 2; i <= n; i++)
    {
        curr = prev + prev2;
        prev2 = prev;
        prev = curr;
    }
    // returning n-1th element because we are starting from 0 index (and question starts from 1st index)
    // so n effectively means n-1
    return prev;
}

int main()
{
    // 0 1 1 2 3 5 8 13 21
    int n = 3;
    int ans1 = fibonacci_tabulation(n);
    int ans2 = fibonacci_optimal(n);
    cout << ans1 << " is answer from tabulation approach" << endl;
    cout << ans2 << " is answer from optimal approach" << endl;
    return 0;
}

// Most Basic Question to start DP from