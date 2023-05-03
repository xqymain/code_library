struct node {
  int left, right;
  int max, min, sum;
};

node tree[maxn << 2];
int a[maxn];
int n;
int k = 1;
int p, q;
string str;

void build(int m, int l, int r)  // m 树的标号
{
  tree[m].left = l;
  tree[m].right = r;
  if (l == r) {
    tree[m].max = tree[m].min = tree[m].sum = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(m << 1, l, mid);
  build(m << 1 | 1, mid + 1, r);
  tree[m].max = max(tree[m << 1].max, tree[m << 1 | 1].max);
  tree[m].min = min(tree[m << 1].min, tree[m << 1 | 1].min);
  tree[m].sum = tree[m << 1].sum + tree[m << 1 | 1].sum;
}

void update(int m, int a, int val) {
  if (tree[m].left == a && tree[m].right == a) {
    tree[m].max += val;
    tree[m].sum += val;
    return;
  }
  int mid = (tree[m].left + tree[m].right) >> 1;
  if (a <= mid)
    update(m << 1, a, val);
  else
    update(m << 1 | 1, a, val);
  tree[m].max = max(tree[m << 1].max, tree[m << 1 | 1].max);
  tree[m].min = min(tree[m << 1].min, tree[m << 1 | 1].min);
  tree[m].sum = tree[m << 1].sum + tree[m << 1 | 1].sum;
}

int querySum(int m, int l, int r) {
  if (l == tree[m].left && r == tree[m].right)
    return tree[m].sum;
  int mid = (tree[m].left + tree[m].right) >> 1;
  if (r <= mid)
    return querySum(m << 1, l, r);
  else if (l > mid)
    return querySum(m << 1 | 1, l, r);
  return querySum(m << 1, l, mid) + querySum(m << 1 | 1, mid + 1, r);
}

int queryMax(int m, int l, int r) {
  if (l == tree[m].left && r == tree[m].right)
    return tree[m].max;
  int mid = (tree[m].left + tree[m].right) >> 1;
  if (r <= mid)
    return queryMax(m << 1, l, r);
  else if (l > mid)
    return queryMax(m << 1 | 1, l, r);
  return max(queryMax(m << 1, l, mid), queryMax(m << 1 | 1, mid + 1, r));
}

int queryMin(int m, int l, int r) {
  if (l == tree[m].left && r == tree[m].right)
    return tree[m].min;
  int mid = (tree[m].left + tree[m].right) >> 1;
  if (r <= mid)
    return queryMin(m << 1, l, r);
  else if (l > mid)
    return queryMin(m << 1 | 1, l, r);
  return min(queryMin(m << 1, l, mid), queryMin(m << 1 | 1, mid + 1, r));
}

void updateRange(int m, int l, int r, int val) {
  if (l == tree[m].left && r == tree[m].right) {
    tree[m].max += val;
    tree[m].min += val;
    tree[m].sum += val * (r - l + 1);
    return;
  }
  int mid = (tree[m].left + tree[m].right) >> 1;
  if (r <= mid)
    updateRange(m << 1, l, r, val);
  else if (l > mid)
    updateRange(m << 1 | 1, l, r, val);
  else {
    updateRange(m << 1, l, mid, val);
    updateRange(m << 1 | 1, mid + 1, r, val);
  }
  tree[m].max = max(tree[m << 1].max, tree[m << 1 | 1].max);
  tree[m].min = min(tree[m << 1].min, tree[m << 1 | 1].min);
  tree[m].sum = tree[m << 1].sum + tree[m << 1 | 1].sum;
}

///
typedef long long ll;
const int maxn = 100010;

int t, n, q;
ll anssum;

struct node {
  ll l, r;
  ll addv, sum;
} tree[maxn << 2];

void maintain(int id) {
  if (tree[id].l >= tree[id].r)
    return;
  tree[id].sum = tree[id << 1].sum + tree[id << 1 | 1].sum;
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
    tree[id].addv = 0;
  }
}

void build(int id, ll l, ll r) {
  tree[id].l = l;
  tree[id].r = r;
  tree[id].addv = 0;
  tree[id].sum = 0;
  if (l == r) {
    tree[id].sum = 0;
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
  scanf("%d", &t);
  int kase = 0;
  while (t--) {
    scanf("%d %d", &n, &q);
    build(1, 1, n);
    int id;
    ll x, y;
    ll val;
    printf("Case %d:\n", ++kase);
    while (q--) {
      scanf("%d", &id);
      if (id == 0) {
        scanf("%lld %lld %lld", &x, &y, &val);
        updateAdd(1, x + 1, y + 1, val);
      } else {
        scanf("%lld %lld", &x, &y);
        anssum = 0;
        query(1, x + 1, y + 1);
        printf("%lld\n", anssum);
      }
    }
  }
  return 0;
}