// by lsl
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, inf = 1e9;
int h[N], nex[N << 1], to[N << 1], tot;
int dep[N], dep2[N], id[N], ans;
int n, s, r1, r2;
int T;
void dfs(int u, int fa) {
  for (int i = h[u]; i; i = nex[i]) {
    int v = to[i];
    if (v == fa) continue;
    dfs(v, u);
    if (dep[v] + 1 > dep[u])
      dep2[u] = dep[u], dep[u] = dep[v] + 1, id[u] = v;
    else if (dep[v] + 1 > dep2[u])
      dep2[u] = dep[v] + 1;
  }
}
void dfs(int u, int fa, int sum) {
  ans = min(ans, max(dep[u], sum));
  for (int i = h[u]; i; i = nex[i]) {
    int v = to[i];
    if (v == fa) continue;
    if (v == id[u])
      dfs(v, u, max(sum + 1, dep2[u] + 1));
    else
      dfs(v, u, max(sum + 1, dep[u] + 1));
  }
}
void add(int x, int y) { to[++tot] = y, nex[tot] = h[x], h[x] = tot; }
void work() {
  for (int i = 1; i <= n; i++) h[i] = dep[i] = dep2[i] = 0;
  tot = 0;
  ans = inf;
  cin >> n >> s >> r1 >> r2;
  for (int i = 1, x, y; i < n; i++) cin >> x >> y, add(x, y), add(y, x);
  dfs(1, 0);
  dfs(1, 0, 0);
  if (ans <= r1 || r2 <= 2 * r1)
    cout << "Kangaroo_Splay\n";
  else
    cout << "General_Kangaroo\n";
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) work();
  return 0;
}
