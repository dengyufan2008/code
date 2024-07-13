#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int d;
  vector<int> e;
} v[1001];
int n, m, d[1001][11];

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
  for (int i = 10; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = d[x][i];
    }
  }
  for (int i = 10; i >= 0; i--) {
    if (d[x][i] != d[y][i]) {
      x = d[x][i], y = d[y][i];
    }
  }
  return x == y ? x : d[x][0];
}

int main() {
  cin >> n >> m;
  for (int i = 2, x; i <= n; i++) {
    cin >> x;
    v[x].e.push_back(i);
  }
  T(0, 1);
  for (int j = 1; j < 11; j++) {
    for (int i = 1; i <= n; i++) {
      d[i][j] = d[d[i][j - 1]][j - 1];
    }
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    cout << Lca(x, y) << '\n';
  }
  return 0;
}
