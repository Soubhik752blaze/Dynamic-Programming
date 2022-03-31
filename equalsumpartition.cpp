/*Question :- Given an array arr[] of size N, 
check if it can be partitioned into two parts such that the sum of elements in both parts is the same.*/

#include<bits/stdc++.h>
using namespace std;

bool isSubsetSum(int set[], int n, int sum)
{
    
    bool subset[n + 1][sum + 1];
    for (int i = 0; i <= n; i++)
        subset[i][0] = true;
    for (int i = 1; i <= sum; i++)
        subset[0][i] = false;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1])
                subset[i][j] = subset[i - 1][j];
            if (j >= set[i - 1])
                subset[i][j] = subset[i - 1][j] || subset[i - 1][j - t[i - 1][j] + val[j]];
        }
    }
    /*for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= sum; j++)
            printf ("%4d", subset[i][j]);
        cout <<"\n";
    }*/
    
    return subset[n][sum];
}

bool ifequalsumpartition(int arr[],int n)
{   
    int sum=0;
    for (int i=0;i<n;i++)
        sum = sum + arr[i];      
    if(sum%2 != 0)
        return false;    
    else
        return isSubsetSum(arr,n,sum/2);

}

int main(){
    int set[] = {2,4,11,10,5};
    int n = sizeof(set) / sizeof(set[0]);    
    if (ifequalsumpartition(set, n) == true)
        cout <<"Equal sum partition is possible!";
    else
        cout <<"Not possible!";
    return 0;
}

