void bag01(int cost,int weight)  {  
    for(i = v; i >= cost; --i)  
        dp[i] = max(dp[i], dp[i-cost]+weight);
}

void complete(int cost, int weight)  {  
    for(i = cost ; i <= v; ++i)  
        dp[i] = max(dp[i], dp[i - cost] + weight);  
}  

void multiply(int cost, int weight, int amount)  {  
    if(cost * amount >= v)  
        complete(cost, weight);  
    else{  
        k = 1;  
        while (k < amount){  
            bag01(k * cost, k * weight);  
            amount -= k;  
            k += k;  
        }  
        bag01(cost * amount, weight * amount);  
    }  
}  

int dp[1000000];
int c[55], m[110];
int sum;

void CompletePack(int c) {
    for (int v = c; v <= sum / 2; ++v)
        dp[v] = max(dp[v], dp[v - c] + c);
}

void ZeroOnePack(int c) {
    for (int v = sum / 2; v >= c; --v)
        dp[v] = max(dp[v], dp[v - c] + c);
}

void multiplePack(int c, int m） {
    if (m * c > sum / 2)
        CompletePack(c);
    else{
        int k = 1;
        while (k < m){
            ZeroOnePack(k * c);
            m -= k;
            k <<= 1;
        }
        if (m != 0)
            ZeroOnePack(m * c);
    }
}

// 最长公共子序列
void solve() {  
    for (int i = 0; i < n; ++i) {  
        for (int j = 0; j < m; ++j)
            if (s1[i] == s2[j])
                dp[i + 1][j + 1] = dp[i][j] + 1;
            else
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);  
}
// 最长上升子序列
void solve(){
    for(int i = 0; i < n; ++i){  
        dp[i] = 1;  
        for(int j = 0; j < i; ++j)
            if(a[j] < a[i])
                dp[i] = max(dp[i], dp[j] + 1);  
    }
} 