// by wls
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
int n, p[N];
vector<int> G[N];
struct Frac {
  __int128_t a, b;
  Frac() : a(0), b(1) {}
  Frac(int x) : a(x), b(1) {}
  Frac(int _a, int _b) : a(_a), b(_b) {}
  inline void cl() {
    int g = __gcd(a, b);
    a /= g, b /= g;
  }
};
bool operator<(const Frac &x, const Frac &y) { return x.a * y.b < x.b * y.a; }
Frac operator+(const Frac &x, const Frac &y) {
  Frac res(x.a * y.b + x.b * y.a, x.b * y.b);
  res.cl();
  return res;
}
Frac f[N];
void dfs(int u, int _f) {
  f[u] = 0;
  for (auto v : G[u]) {
    if (v == _f) continue;
    dfs(v, u);
    f[u] = max(f[u], f[v]);
  }
  f[u] = f[u] + Frac(15, p[u]);
}
void print(__int128_t x) {
  if (x < 0) cout << '-', x = -x;
  if (x > 9) print(x / 10);
  cout << char(x % 10 + '0');
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
      cin >> u >> v;
      G[u].push_back(v), G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) cin >> p[i];
    dfs(1, 0);
    print(f[1].a), cout << '/', print(f[1].b), cout << '\n';
    for (int i = 1; i <= n; i++) f[i] = 0, G[i].clear();
  }
  return 0;
}
