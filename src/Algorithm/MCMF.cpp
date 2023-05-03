#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
namespace dinic {
const int N = 1e5 + 7, M = 2e6 + 7;
const ll INF = 0x3f3f3f3f3f;
int n, S, T;
int head[N], ver[M], nex[M], tot, cur[N];
ll dist[N], edge[M], cost[M], maxflow, mincost;
bool vis[N];
inline void add(int x, int y, ll z, ll c, bool o = 1) {
  ver[tot] = y;
  edge[tot] = z;
  cost[tot] = c;
  nex[tot] = head[x];
  head[x] = tot++;
  if (o)
    add(y, x, 0, -c, 0);
}
inline bool spfa() {
  // memset(dist, 0x3f, sizeof dist);
  for (int i = 1; i <= n; ++i)
    dist[i] = INF;
  memset(vis, 0, sizeof vis);
  queue<int> q;
  q.push(S);
  dist[S] = 0;
  vis[S] = 1;
  while (q.size()) {
    int x = q.front();
    q.pop();
    vis[x] = 0;
    for (int i = head[x]; ~i; i = nex[i]) {
      int y = ver[i];
      ll z = edge[i], c = cost[i];
      if (dist[y] <= dist[x] + c || !z)
        continue;
      dist[y] = dist[x] + c;
      if (!vis[y])
        q.push(y), vis[y] = 1;
    }
  }
  return dist[T] != INF;
}
ll dfs(int x, ll flow = INF) {
  if (x == T)
    return flow;
  ll ans = 0, k, i;
  vis[x] = 1;
  for (i = cur[x]; ~i && flow; i = nex[i]) {
    cur[x] = i;
    int y = ver[i];
    ll z = edge[i], c = cost[i];
    if (!z || (dist[y] != dist[x] + c) || vis[y])
      continue;
    k = dfs(y, min(flow, z));
    if (!k)
      dist[y] = INF;
    edge[i] -= k;
    edge[i ^ 1] += k;
    ans += k, mincost += k * c, flow -= k;
  }
  vis[x] = 0;
  return ans;
}
inline void main() {
/*   while (spfa()) {
    for (int i = 1; i <= n; ++i)
      cur[i] = head[i];
    // memcpy(cur, head, sizeof head);
    ll now;
    while ((now = dfs(S)))
      maxflow += now;
  } */
  while (spfa()) {
    memcpy(cur, head, sizeof(int[n + 1]));
    maxflow += dfs(S);
    memset(vis, 0, sizeof(bool[n + 1]));
  }
  return;
}
inline void init(int _n, int _S, int _T) {
  n = _n, S = _S, T = _T, tot = 0, maxflow = 0, mincost = 0;
  memset(head, -1, sizeof head);
}
}//namespace dinic

int n, m, S, T;
int main() {
  qcin>>n>>m>>S>>T;
  dinic::init(n, S, T);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    ll z, c;
    qcin>>x>>y>>z>>c;
    dinic::add(x, y, z, c, 1);
  }
  dinic::main();
  qcout<<dinic::maxflow<<" "<<dinic::mincost;
  return 0;
}