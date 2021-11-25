#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int d, c;
  vector<int> e;
} v[300001];
int n, a[300001], d[300001][19];

int T(int f, int x) {
  v[x].d = v[f].d + 1, d[x][0] = f;
  for (int i : v[x].e) {
    if (f != i) {
      v[x].c += T(x, i);
    }
  }
  return v[x].c;
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
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, 1);
  for (int j = 1; j < 19; j++) {
    for (int i = 1; i <= n; i++) {
      d[i][j] = d[d[i][j - 1]][j - 1];
    }
  }
  for (int i = 1; i < n; i++) {  // a[i] -> a[i + 1]
    int c = Lca(a[i], a[i + 1]);
    v[a[i]].c++, v[d[a[i + 1]][0]].c++, v[c].c--, v[d[c][0]].c--;
  }
  T(0, 1);
  for (int i = 1; i <= n; i++) {
    cout << v[i].c << '\n';
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
