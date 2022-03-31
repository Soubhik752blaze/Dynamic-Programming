/*Rod Cutting Problem
Given a rod of length n inches and an array of prices that contains prices of all pieces of size smaller than n. 
 Determine the  maximum value obtainable by cutting up the rod and selling the pieces. 
 Example: 
if length of the rod is 8 and the values of different pieces are given as following, then the maximum obtainable value is 22 (by cutting in two pieces of lengths 2 and 6)


length   | 1   2   3   4   5   6   7   8  
--------------------------------------------
price    | 1   5   8   9  10  17  17  20*/
#include<bits/stdc++.h>
using namespace std;

int rodcutmaxprice(int l, int n, int w[], int val[])
{
    int t[n+1][l+1];
    int i,j;
    for(i=0;i<n+1;i++)
        t[i][0] = 0 ;
    for(i=0;i<l+1;i++)  
        t[0][i] = 0 ;

    for(i=1;i<n+1;i++)
        for(j=1;j<l+1;j++)
            {
                if(w[i-1]>j)
                    t[i][j]=t[i-1][j];
                else
                    t[i][j]=max(t[i-1][j],val[i-1]+t[i][j-w[i-1]]);        
            }
    return t[n][l];              

}
int main()
{
    system("cls");
    int l = 8;          /*length of rod*/
    int length[]={1,2,3,4,5,6,7,8};         /*length array*/
    int price[]={1, 5, 8, 9, 10, 17, 17, 20};
    int n = sizeof(length)/sizeof(length[0]);     /*Price array*/
    int maxprice=rodcutmaxprice(l,n,length,price);
    cout<<maxprice;
    return 0;
}