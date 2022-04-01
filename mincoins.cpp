/*Coin Change Problem Minimum Numbers of coins
Given a value V, if we want to make change for V cents, and we have infinite supply of each of C = { C1, C2, .. , Cm} valued coins, what is the minimum number of coins to make the change?
Example:

Input: coins[] = {25, 10, 5}, V = 30
Output: Minimum 2 coins required
We can use one coin of 25 cents and one of 5 cents */
#include<bits/stdc++.h>
using namespace std;

int mincoins(int sum, int n, int coins[])
{
    int t[n+1][sum+1];
    int i,j;
    
    for(i=0;i<n+1;i++)
        t[i][0] = 0 ;    

    for(i=0;i<sum+1;i++)  
        t[0][i] = INT_MAX - 1 ;

    for(i=1,j=0;j<sum+1;j++)
        {
            if(j%coins[i]==0)
                t[i][j]=(j / coins[i]);
            else    
                t[i][j] = INT_MAX - 1;
        }
    for(i=2;i<n+1;i++)
        for(j=1;j<sum+1;j++)
            {
                if(coins[i-1]>j)
                    t[i][j]= t[i-1][j];
                else
                    t[i][j]= min(t[i-1][j], 1 + t[i][j-coins[i-1]]);        
            }
    return t[n][sum];              

}
int main()
{
    system("cls");
    int sum = 4;          /*target*/
    int coins[]={3,6,5};         /*coins array*/
    int n = sizeof(coins)/sizeof(coins[0]);     /*length of coins array*/
    int noofcoins=mincoins(sum,n,coins);
    if(noofcoins !=2147483646)
        cout<<noofcoins;
    else    
        cout<<"Coins donot Add up to sum!"; 
    return 0;
}