#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int d;
  vector<int> e;
} v[500001];
int n, m, x, y, z, d[500001][19];

int Read() {
  int f(1), x(0);
  char ch(getchar());
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch > '/' && ch < ':') {
    x = (x << 3) + (x << 1) + (ch - '0');
    ch = getchar();
  }
  return f * x;
}

void T(int f, int x) {
  v[x].d = v[f].d + 1, d[x][0] = f;
  for (int i : v[x].e) {
    if (f != i) {
      T(x, i);
    }
  }
}

int Lca(int x, int y) {
  if (v[x].d < v[y].d) {
    swap(x, y);
  }
  for (int i = 18; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = d[x][i];
    }
  }
  for (int i = 18; i >= 0; i--) {
    if (d[x][i] != d[y][i]) {
      x = d[x][i], y = d[y][i];
    }
  }
  return x == y ? x : d[x][0];
}

int main() {
  n = Read(), m = Read();
  for (int i = 1, x, y; i < n; i++) {
    x = Read(), y = Read();
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, 1);
  for (int j = 1; j <= 18; j++) {
    for (int i = 1; i <= n; i++) {
      d[i][j] = d[d[i][j - 1]][j - 1];
    }
  }
  while (m--) {
    x = Read(), y = Read(), z = Read();
    int p[3] = {Lca(x, y), Lca(x, z), Lca(y, z)};
    for (int i = 0; i < 3; i++) {
      if (p[i] == p[(i + 1) % 3]) {
        cout << p[(i + 2) % 3];
        break;
      }
    }
    cout << ' ' << v[x].d + v[y].d + v[z].d - v[p[0]].d - v[p[1]].d - v[p[2]].d << '\n';
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}