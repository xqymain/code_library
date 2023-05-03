#include <bits/stdc++.h>
using namespace std;
const int v = 50;    // 背包容量
int dp[v+1];

void bag01(int cost,int weight)  {  
    for(int i = v; i >= cost; --i)  
        dp[i] = max(dp[i], dp[i-cost]+weight);
}

void complete(int cost, int weight)  {  
    for(int i = cost ; i <= v; ++i)  
        dp[i] = max(dp[i], dp[i - cost] + weight);  
}  

void multiply(int cost, int weight, int amount)  {  
    if(cost * amount >= v)  
        complete(cost, weight);  
    else{  
        int k = 1;    // 二进制拆分
        while (k < amount){  
            bag01(k * cost, k * weight);  
            amount -= k;  
            k += k;  
        }  
        bag01(cost * amount, weight * amount);  
    }  
}

qcout << dp[v];

// 最长公共子序列 LCS
int n,m,dp[1005][1005];
char* s1,s2;
void solve(){
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (s1[i] == s2[j])
                dp[i + 1][j + 1] = dp[i][j] + 1;
            else
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);  
}

qcout << dp[n][m];

// 最长上升子序列 LIS
int n,a[1005],dp[1005];
void solve(){
    for(int i = 0; i < n; ++i){  
        dp[i] = 1;  
        for(int j = 0; j < i; ++j)
            if(a[j] < a[i])
                dp[i] = max(dp[i], dp[j] + 1);  
    }
}

qcout << *max_element(dp,dp+n);

// 最长下降子序列 LDS
reverse(a,a+n);