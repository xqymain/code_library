int n, m;
int parent[10005], rankk[10005];

int find(int x) {
  if (x == parent[x])
    return x;
  return parent[x] = find(parent[x]);  // 路径压缩
}

void merge(int x, int y) {
  int X = find(x), Y = find(y);
  if (X == Y)
    return;

  // 按秩合并
  if (rankk[X] > rankk[Y]) {
    parent[Y] = X;
  } else {
    parent[X] = Y;
    if (rankk[X] == rankk[Y])
      rankk[Y]++;
  }
}

int main() {
  qcin >> n >> m;

  for (int i = 1; i <= n; i++)
    parent[i] = i;
  for (int i = 0; i < m; i++) {
    int z, x, y;
    qcin >> z >> x >> y;
    if (z == 1)
      merge(x, y);
    if (z == 2) {
      if (find(x) == find(y))
        qcout << "Y" << '\n';
      else
        qcout << "N" << '\n';
    }
  }
  return 0;
}
