struct node {  
    int v, len; // v终点 len边权
    node(int v = 0, int len = 0) :v(v), len(len) {}  
    bool operator < (const node &a)const {  //  距离从小到大排序
        return len > a.len;  
    }  
};  
vector<node> G[maxn];
bool inqueue[maxn];
int dist[maxn];

void Init()  
{  
    for(int i = 0 ; i < maxn ; ++i){  
        G[i].clear();  
        dist[i] = INF;  
    }  
}  
int SPFA(int s,int e)
{  
    int v1,v2,weight;  
    queue<int> Q;  
    memset(inqueue,false,sizeof(inqueue));
    memset(cnt,0,sizeof(cnt));
    dist[s] = 0;  
    Q.push(s);
    inqueue[s] = true;
    while(!Q.empty()){  
        v1 = Q.front();  
        Q.pop();  
        inqueue[v1] = false;
        for(int i = 0 ; i < G[v1].size() ; ++i){
            v2 = G[v1][i].vex;  
            weight = G[v1][i].weight;  
            if(dist[v2] > dist[v1] + weight){ 
                dist[v2] = dist[v1] + weight;  
                if(inqueue[v2] == false){
                    inqueue[v2] = true;  
                    //cnt[v2]++;  // 判负环  
                    //if(cnt[v2] > n) return -1;  
                    Q.push(v2);  
                } } }  
    }  
    return dist[e];  
}
