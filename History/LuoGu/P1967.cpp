#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct E {
  int x, y, v;
  bool operator<(const E &e) const {
    return v < e.v;
  }
} e[50001];
struct V {
  int d;
  vector<pair<int, int>> e;
} v[10001];
int n, m, q, x, y, f[10001], d[10001][14], _d[10001][14];

int GetRoot(int x) {
  return f[x] == x ? x : f[x] = GetRoot(f[x]);
}

void SpawnTree() {
  sort(e + 1, e + m + 1);
  for (int i = 1; i <= n; i++) {
    f[i] = i;
  }
  for (int i = m; i; i--) {
    if (GetRoot(e[i].x) != GetRoot(e[i].y)) {
      f[GetRoot(e[i].x)] = GetRoot(e[i].y);
      v[e[i].x].e.push_back({e[i].y, e[i].v});
      v[e[i].y].e.push_back({e[i].x, e[i].v});
    }
  }
}

void T(int f, int x) {
  v[x].d = v[f].d + 1, d[x][0] = f;
  for (auto i : v[x].e) {
    if (f != i.first) {
      _d[i.first][0] = i.second;
      T(x, i.first);
    }
  }
}

void MakeST() {
  for (int j = 1; j <= 13; j++) {
    for (int i = 1; i <= n; i++) {
      d[i][j] = d[d[i][j - 1]][j - 1];
      _d[i][j] = min(_d[i][j - 1], _d[d[i][j - 1]][j - 1]);
    }
  }
}

int Lca(int x, int y) {
  int ans = 114514;
  if (v[x].d < v[y].d) {
    swap(x, y);
  }
  for (int i = 13; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      ans = min(ans, _d[x][i]);
      x = d[x][i];
    }
  }
  for (int i = 13; i >= 0; i--) {
    if (d[x][i] != d[y][i]) {
      ans = min(ans, min(_d[x][i], _d[y][i]));
      x = d[x][i], y = d[y][i];
    }
  }
  return x == y ? ans : min(ans, min(_d[x][0], _d[y][0]));
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> e[i].x >> e[i].y >> e[i].v;
  }
  SpawnTree();
  for (int i = 1; i <= n; i++) {
    if (!v[i].d) {
      T(0, i);
    }
  }
  MakeST();
  cin >> q;
  while (q--) {
    cin >> x >> y;
    int c = Lca(x, y);
    cout << (c == 0 ? -1 : c) << '\n';
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
