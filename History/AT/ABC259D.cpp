#include <cmath>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL x, y, r;
} v[3001];
LL n, sx, sy, tx, ty, s, t, f[3001];

LL GetRoot(LL x) {
  return f[x] == x ? x : f[x] = GetRoot(f[x]);
}

LL D(LL x1, LL y1, LL x2, LL y2) {
  return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
  cin >> n >> sx >> sy >> tx >> ty;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].x >> v[i].y >> v[i].r;
    f[i] = i;
    if (!s && D(v[i].x, v[i].y, sx, sy) == v[i].r * v[i].r) {
      s = i;
    }
    if (!t && D(v[i].x, v[i].y, tx, ty) == v[i].r * v[i].r) {
      t = i;
    }
    for (LL j = 1; j < i; j++) {
      if (D(v[i].x, v[i].y, v[j].x, v[j].y) <= (v[i].r + v[j].r) * (v[i].r + v[j].r) && D(v[i].x, v[i].y, v[j].x, v[j].y) >= (v[i].r - v[j].r) * (v[i].r - v[j].r)) {
        f[GetRoot(i)] = GetRoot(j);
      }
    }
  }
  cout << (f[GetRoot(s)] == f[GetRoot(t)] ? "Yes" : "No");
  return 0;
}
