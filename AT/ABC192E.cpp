#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  LL p, d, t, k;
} e[200002];
struct B {
  LL et, d = 1e18;
} v[100001];
LL n, m, x, y;

void T(int f, int x) {
  for (int i = v[x].et; i; i = e[i].p) {
    if (e[i].d != f) {
      v[e[i].d].d = min(v[e[i].d].d, v[x].d + e[i].t + v[x].d % e[i].k);
      T(x, e[i].d);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m >> x >> y;
  for (LL i = 1, a, b, c, d; i <= m; i++) {
    cin >> a >> b >> c >> d;
    e[i * 2] = {v[a].et, b, c, d}, v[a].et = i * 2;
    e[i * 2 + 1] = {v[b].et, a, c, d}, v[b].et = i * 2 + 1;
  }
  v[x].d = 0;
  T(0, x);
  cout << (v[y].d == 1e18 ? -1 : v[y].d) << endl;
  return 0;
}
