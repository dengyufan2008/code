#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int d, v;
  vector<int> e;
} v[50001];
int n, k, x, y, ans, d[50001][17];

void T(int f, int x) {
  v[x].d = v[f].d + 1, d[x][0] = f;
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i);
    }
  }
}

int _T(int f, int x) {
  int ans = v[x].v;
  for (int i : v[x].e) {
    if (i != f) {
      ans += _T(x, i);
    }
  }
  return v[x].v = ans;
}

int Lca(int x, int y) {
  if (v[x].d < v[y].d) {
    swap(x, y);
  }
  for (int i = 16, p = v[x].d; i >= 0; i--) {
    if (p - (1 << i) >= v[y].d) {
      x = d[x][i], p -= 1 << i;
    }
  }
  int _x = x, _y = y;
  for (int i = 16; i >= 0; i--) {
    if (d[_x][i] != d[_y][i]) {
      _x = d[_x][i], _y = d[_y][i];
    }
  }
  return _x == _y ? _x : d[_x][0];
}

int main() {
  cin >> n >> k;
  for (int i = 1; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, 1);
  for (int i = 1; i <= 16; i++) {
    for (int j = 1; j <= n; j++) {
      d[j][i] = d[d[j][i - 1]][i - 1];
    }
  }
  while (k--) {
    cin >> x >> y;
    int z = Lca(x, y);
    v[x].v++, v[d[z][0]].v--, v[y].v++, v[z].v--;
  }
  _T(0, 1);
  for (int i = 1; i <= n; i++) {
    ans = max(ans, v[i].v);
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
