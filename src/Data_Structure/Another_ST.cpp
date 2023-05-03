#include <algorithm>
#include <cstdio>
typedef long long ll;
const int maxn = 100010;

int t, n, q;
ll anssum, ansmin, ansmax;

struct node {
  ll l, r;
  ll addv, sum, maxv, minv;
} tree[maxn << 2];

void maintain(int id) {
  if (tree[id].l >= tree[id].r)
    return;
  tree[id].sum = tree[id << 1].sum + tree[id << 1 | 1].sum;
  tree[id].maxv = std::max(tree[id << 1].maxv, tree[id << 1 | 1].maxv);
  tree[id].minv = std::min(tree[id << 1].minv, tree[id << 1 | 1].minv);
}

void pushdown(int id) {
  if (tree[id].l >= tree[id].r)
    return;
  if (tree[id].addv) {
    int tmp = tree[id].addv;
    tree[id << 1].addv += tmp;
    tree[id << 1 | 1].addv += tmp;
    tree[id << 1].sum += (tree[id << 1].r - tree[id << 1].l + 1) * tmp;
    tree[id << 1 | 1].sum +=
        (tree[id << 1 | 1].r - tree[id << 1 | 1].l + 1) * tmp;
    tree[id << 1].maxv += tmp;
    tree[id << 1 | 1].maxv += tmp;
    tree[id << 1].minv += tmp;
    tree[id << 1 | 1].minv += tmp;
    tree[id].addv = 0;
  }
}

void build(int id, ll l, ll r) {
  tree[id].l = l;
  tree[id].r = r;
  tree[id].addv = 0;
  tree[id].sum = 0;
  tree[id].maxv = -1e18;
  tree[id].minv = 1e18;
  if (l == r) {
    tree[id].sum = 0;
    tree[id].maxv = 0;
    tree[id].minv = 0;
    return;
  }
  ll mid = (l + r) >> 1;
  build(id << 1, l, mid);
  build(id << 1 | 1, mid + 1, r);
  maintain(id);
}

void updateAdd(int id, ll l, ll r, ll val) {
  if (tree[id].l >= l && tree[id].r <= r) {
    tree[id].addv += val;
    tree[id].sum += (tree[id].r - tree[id].l + 1) * val;
    tree[id].maxv += val;
    tree[id].minv += val;
    return;
  }
  pushdown(id);
  ll mid = (tree[id].l + tree[id].r) >> 1;
  if (l <= mid)
    updateAdd(id << 1, l, r, val);
  if (mid < r)
    updateAdd(id << 1 | 1, l, r, val);
  maintain(id);
}

void query(int id, ll l, ll r) {
  if (tree[id].l >= l && tree[id].r <= r) {
    anssum += tree[id].sum;
    ansmax = std::max(ansmax, tree[id].maxv);
    ansmin = std::min(ansmin, tree[id].minv);
    return;
  }
  pushdown(id);
  ll mid = (tree[id].l + tree[id].r) >> 1;
  if (l <= mid)
    query(id << 1, l, r);
  if (mid < r)
    query(id << 1 | 1, l, r);
  maintain(id);
}
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    build(1,1,n+1);
    for(int i=1,num;i<=n;i++)
    {
      scanf("%d",&num);
      updateAdd(1,i+1,i+1,num);
    }
    for(int i=1;i<=m;i++)
    {
        int q,x,y,z;
        scanf("%d",&q);
        if(q==1){
            scanf("%d%d%d",&x,&y,&z);
            updateAdd(1,x+1,y+1,z);
        }
        else {
        scanf("%d %d", &x, &y);
        anssum = 0;
        ansmax = -1e18;
        ansmin = 1e18;
        query(1, x + 1, y + 1);
        printf("Sum: %lld, Max: %lld, Min: %lld\n", anssum, ansmax, ansmin);
        }
    }
}