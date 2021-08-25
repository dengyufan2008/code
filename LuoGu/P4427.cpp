#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const LL kMod = 998244353;
struct V {
  LL d, v[51];
  vector<LL> e;
} v[300001];
LL n, m, x, y, k, d[300001][20];

LL Pow(LL a, LL x) {
  LL b = a, ans = 1;
  for (LL i = 1; i <= x; i <<= 1) {
    if (x & i) {
      ans = (ans * b) % kMod;
    }
    b = (b * b) % kMod;
  }
  return ans;
}

void T(LL f, LL x) {
  d[x][0] = f, v[x].d = v[f].d + 1;
  for (LL i = 1; i <= 50; i++) {
    v[x].v[i] = (v[f].v[i] + Pow(v[x].d, i)) % kMod;
  }
  for (LL i : v[x].e) {
    if (i != f) {
      T(x, i);
    }
  }
}

LL Lca(LL x, LL y) {
  if (v[x].d < v[y].d) {
    swap(x, y);
  }
  for (LL i = 19, p = v[x].d; i >= 0; i--) {
    if (p - (1 << i) >= v[y].d) {
      x = d[x][i], p -= 1 << i;
    }
  }
  LL _x = x, _y = y;
  for (LL i = 19; i >= 0; i--) {
    if (d[_x][i] != d[_y][i]) {
      _x = d[_x][i], _y = d[_y][i];
    }
  }
  return _x == _y ? _x : d[_x][0];
}

int main() {
  cin >> n;
  for (LL i = 1; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  v[0].d = -1;
  T(0, 1);
  for (LL i = 1; i <= 19; i++) {
    for (LL j = 1; j <= n; j++) {
      d[j][i] = d[d[j][i - 1]][i - 1];
    }
  }
  cin >> m;
  while (m--) {
    cin >> x >> y >> k;
    LL z = Lca(x, y);
    cout << ((v[x].v[k] - v[d[z][0]].v[k] + v[y].v[k] - v[z].v[k]) % kMod + kMod) % kMod << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
