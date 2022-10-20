/*Question :- Target Sum Problem
Given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. 
For each integer, you should choose one from + and - as its new symbol.
Find out how many ways to assign symbols to make sum of integers equal to target S.


                    THIS QUESTION IS SAME AS "COUNT NO OF SUBSETS WITH A GIVEN DIFFERENCE OF SUBSETSUM"       */

#include<bits/stdc++.h>
using namespace std;

int findTargetSumWays(vector<int>&A ,int target)
    {
        int S=target;
        int sum = 0;
        int n =A.size();
        for(int i =0;i<n;i++)
            sum += A[i];
        if(S>sum || (sum-S)%2!=0)
            return 0;
        
        int dp[n+1][((sum-S)/2)+1];
        
        int c=0;
        for(int i=0;i<n;i++)
            if(A[i]==0)
                c++;
        
        for(int i=0;i<n+1;i++)
            dp[i][0]=1;    
            
        for(int i=1;i<((sum-S)/2)+1;i++)
            dp[0][i] = 0;
        
        for(int i=1;i<n+1;i++)
            for(int j=1;j<((sum-S)/2)+1;j++)
            {
                if(A[i-1]==0)
                    dp[i][j] = dp[i-1][j];
                else
                if(A[i-1]<=j)
                    dp[i][j] = dp[i-1][j-A[i-1]] + dp[i-1][j];
                else
                    dp[i][j] = dp[i-1][j];
            }
        
        
        return pow(2,c)*dp[n][(sum-S)/2];
        }



int main() 
{
    int target = 1,n=3;
    vector<int> A(n);
    for(int i=0;i<n;i++)
        cin>>A[i];
    cout<<"No of ways: "<<findTargetSumWays(A,target);
    }
     
      
