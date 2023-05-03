#include <bits/stdc++.h>
using namespace std;
// import IO + LCT
// Sol1: Kruskal 稀疏图
typedef pair<int, int> PII;
const int N = 2e5 + 7;
int fa[N], rankk[N], n, m, ans;
struct node {
  int x, y, z;
  bool operator<(node& t) const { return z < t.z; }
} edge[N];

int main() {
  qcin >> n >> m; // n点m边
  int cnt = n;
  for (int i = 1; i <= m; ++i)
    qcin >> edge[i].x >> edge[i].y >> edge[i].z;
  sort(edge + 1, edge + 1 + m);
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  for (int i = 1; i <= m; ++i) {
    if (merge(edge[i].x, edge[i].y)) {
      ans += edge[i].z;
      --cnt;
    }
  }
  if (cnt-1)
    puts("orz");
  else
    qcout << ans;
}

// Sol2: Prim 稠密图
typedef long long ll;
typedef pair<int, int> PII;
const int N = 4e5 + 7;

int ver[N], nex[N], edge[N], head[N], tot;
int n, m, ans;
int dis[N];
int vis[N], cnt;
void add(int u, int v, int val) {
  ver[++tot] = v;
  edge[tot] = val;
  nex[tot] = head[u];
  head[u] = tot;
}
priority_queue<PII, vector<PII>, greater<PII> > q;
void prim() {
  dis[1] = 0;
  q.push({0, 1});
  while (q.size() && cnt != n) {
    int d = q.top().first, u = q.top().second;
    q.pop();
    if (vis[u])
      continue;
    cnt++;
    ans += d;
    vis[u] = 1;
    for (int i = head[u]; i; i = nex[i]) {
      int v = ver[i];
      if (edge[i] < dis[v])
        dis[v] = edge[i], q.push({dis[v], v});
    }
  }
}
int main() {
  memset(dis, 0x3f, sizeof dis);
  qcin>>n>>m;
  for (int i = 1; i <= m; i++) {
    int x, y, z;
    qcin>>x>>y>>z;
    add(x, y, z);
    add(y, x, z);
  }
  prim();
  if (cnt == n)
    qcout<<ans;
  else
    puts("orz");
  return 0;
}