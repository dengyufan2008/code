#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  LL p, d;
} e[200001];
struct B {
  LL et, d, f;
} v[200001];
LL n, m, ans = -1e18;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].d;
    v[i].f = v[i].d;
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    e[i] = {v[x].et, y}, v[x].et = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = v[i].et; j; j = e[j].p) {
      v[e[j].d].f = min(v[e[j].d].f, v[i].f);
    }
    ans = max(ans, v[i].et ? v[i].d - v[i].f : (LL)(-1e18));
  }
  cout << ans << endl;
  return 0;
}
