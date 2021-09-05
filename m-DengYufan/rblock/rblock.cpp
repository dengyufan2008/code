#include <ctime>
#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct V {
  LL d, p, e[251];
} v[251];
LL n, m, d, ans;
priority_queue<pair<LL, LL>> h;

inline int Input() {
  register int x(0), f;
  register char ch = getchar();
  f = ch == '-' ? -1 : 1;
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch - '0');
    ch = getchar();
  }
  return f * x;
}

inline void M() {
  for (LL i(1); i <= n; ++i) {
    v[i].d = 0x7fffffff, v[i].p = 0;
  }
  v[1].d = 0;
  for (h.push({0, 1}); !h.empty();) {
    auto p = h.top();
    h.pop();
    for (LL i(1); i <= n; ++i) {
      if (v[i].d > v[p.second].d + v[p.second].e[i]) {
        v[i].d = v[p.second].d + v[p.second].e[i];
        v[i].p = p.second;
        h.push({-v[i].d, i});
      }
    }
  }
}

int main() {
  freopen("rblock.in", "r", stdin);
  freopen("rblock.out", "w", stdout);
  n = Input(), m = Input();
  for (LL i(1); i <= n; ++i) {
    fill(&v[i].e[0], &v[i].e[250] + 1, 0x7fffffff);
  }
  for (LL i(1), x, y, z; i <= m; ++i) {
    x = Input(), y = Input(), z = Input();
    v[x].e[y] = min(v[x].e[y], z), v[y].e[x] = min(v[y].e[x], z);
  }
  M();
  d = v[n].d;
  for (int i(n); v[i].p; i = v[i].p) {
    v[i].e[v[i].p] <<= 1, v[v[i].p].e[i] <<= 1;
    M();
    ans = max(ans, v[n].d - d);
    v[i].e[v[i].p] >>= 1, v[v[i].p].e[i] >>= 1;
  }
  cout << ans << '\n';
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
