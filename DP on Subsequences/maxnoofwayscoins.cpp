/*Coin Change Problem Maximum Number of ways
Given a value N, if we want to make change for N cents, and we have infinite supply of each of S = { S1, S2, .. , Sm} valued coins, 
how many ways can we make the change? The order of coins doesn’t matter.
Example:
for N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},{1,1,2},{2,2},{1,3}. So output should be 4.*/
#include<bits/stdc++.h>
using namespace std;

int maxwaysforcoin(int l, int n, int coins[])
{
    int t[n+1][l+1];
    int i,j;
    
    for(i=0;i<l+1;i++)  
        t[0][i] = 0 ;

    for(i=0;i<n+1;i++)
        t[i][0] = 1 ;    

    for(i=1;i<n+1;i++)
        for(j=1;j<l+1;j++)
            {
                if(coins[i-1]>j)
                    t[i][j]= t[i-1][j];
                else
                    t[i][j]= t[i-1][j] + t[i][j-coins[i-1]];        
            }
    return t[n][l];              

}
int main()
{
    system("cls");
    int sum = 1000;          /*length of rod*/
    int coins[]={100,200,500};         /*length array*/
    int n = sizeof(coins)/sizeof(coins[0]);     /*Price array*/
    int maxways=maxwaysforcoin(sum,n,coins);
    cout<<maxways;
    return 0;
}