// Question:- Given n as no of stairs, find the no of ways to reach nth stair,
// It is given that from ith stair, you can go i+1th stair or i+2th stair directly..
#include <bits/stdc++.h>
using namespace std;

int countwaystillnstairs(int n)
{
    //Using Tabulation method
    //TC -> o(n), SC -> o(1)

    //Intuition :- Any nth step is reachable from (n-1)th or (n-2)th step
    //So technically no of ways to reach nth step = no of ways to reach (n-1)th step + no of ways to reach (n-2)th step
    // This becomes thus a variation of fibonacci no
    int curr;
    int n1 = 1; // 1 step to reach 0th step
    int n2 = 1; // 1 step to reach 1th step
    for (int i = 2; i <= n; i++)
    {
        curr = n1 + n2;
        n1 = n2;
        n2 = curr;
    }
    //returning n element because we are starting from 0th stair (by problem itself) so we return nth element
    return n2;
}

int main()
{
    int n = 2;
    int ans = countwaystillnstairs(n);
    cout << ans << " are the no of ways possible"<<endl;

    return 0;
}

//Variation of fibonaci number question