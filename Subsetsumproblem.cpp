/*Question :- Given a set of non-negative integers, and a value sum, 
determine if there is a subset of the given set with sum equal to given sum. */

#include <bits/stdc++.h>
using namespace std;


int issubsetsum(int arr[],int n,int w){
    int t[n+1][w+1];

    for (int i = 0; i <= n; i++)
        t[i][0] = true;
                                                    /*DP_MATRIX_INITIALISING*/
    for (int j = 1; j <= w; j++)
        t[0][j] = false;


    for(int i=1;i<=n;i++)
        for(int j=1;j<=w;j++){
            if(arr[i-1]>j)
                t[i][j] = t[i-1][j];                    /*DP_RESULTS_STORING*/
            else
                t[i][j] = t[i-1][j-arr[i-1]] || t[i-1][j];
        }    

    return t[n][w];

}

int main(){
    int arr[]= {3, 34, 4, 12, 5, 2};
    int w = 17;
    int n = sizeof(arr)/sizeof(arr[0]);
    if (issubsetsum(arr, n, w) == true)
        cout <<"Found a subset with given sum!";
    else
        cout <<"Sorry, No subset with given sum!";
    return 0;
}

