#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int d;
  vector<int> e;
} v[100001];
int n, m, s, d[100001][21];

void T(int f, int x) {
  for (int i : v[x].e) {
    if (i != f) {
      v[i].d = v[x].d + 1, d[i][0] = x;
      T(x, i);
    }
  }
}

int Lca(int x, int y) {
  if (v[x].d < v[y].d) {
    swap(x, y);
  }
  for (int i = 20; i >= 0; i--) {
    if ((1 << i) & (v[x].d - v[y].d)) {
      x = d[x][i];
    }
  }
  for (int i = 20, h = v[x].d; i >= 0; i--) {
    if (h - (1 << i) >= 0 && d[x][i] != d[y][i]) {
      x = d[x][i], y = d[y][i];
    }
  }
  return x == y ? x : d[x][0];
}

int main() {
  cin >> n >> m;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, s);
  for (int i = 1; i <= 20; i++) {
    for (int j = 1; j <= n; j++) {
      d[j][i] = d[d[j][i - 1]][i - 1];
    }
  }
  for (int i = 1, x1, y1, x2, y2; i <= m; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    int z1 = Lca(x1, y1), z2 = Lca(x2, y2);
    cout << ((Lca(x2, z1) == z1 || Lca(y2, z1) == z1) && (Lca(x1, z2) == z2 || Lca(y1, z2) == z2) ? "Y" : "N") << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
