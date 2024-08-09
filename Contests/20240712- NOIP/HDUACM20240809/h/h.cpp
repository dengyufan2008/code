// by lsl
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 205, mod = 1e9 + 7;
struct mat {
  ll a[N][N], n;
  void clear() { memset(a, 0, sizeof(a)); }
  void init() {
    clear();
    for (int i = 0; i < n; i++) a[i][i] = 1;
  }
  void out() {
    for (int i = 0; i < n; i++, cout << '\n')
      for (int j = 0; j < n; j++) cout << a[i][j] << ' ';
  }
};
mat base, sb, st;
mat operator*(mat a, mat b) {
  mat c;
  c.clear();
  c.n = a.n;
  for (int i = 0; i < c.n; i++)
    for (int j = 0; j < c.n; j++) {
      __int128 x = 0;
      for (int k = 0; k < c.n; k++)
        x += a.a[i][k] * b.a[k][j];
      c.a[i][j] = x % mod;
    }
  return c;
}
mat ksm(mat a, ll b, int n) {
  mat res;
  res.n = n;
  res.init();
  while (b) {
    if (b & 1) res = res * a;
    a = a * a, b >>= 1;
  }
  return res;
}
vector<pair<int, int>> G[N];
int in[N], d[N];
ll sum[N], dp[N][N];
int n, m, T;
ll L, R, ans;
void work() {
  memset(dp, 0, sizeof(dp));
  memset(in, 0, sizeof(in));
  memset(sum, 0, sizeof(sum));
  ans = 0;
  for (int i = 0; i < n; i++) G[i].clear();
  cin >> n >> m >> L >> R;
  L--, R--;
  base.n = st.n = n;
  sb.n = 2 * n;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    x--, y--;
    G[x].push_back(make_pair(y, z));
    in[y]++;
  }
  for (int i = 0; i < n; i++) {
    dp[i][i] = 1;
    queue<int> q;
    for (int j = 0; j < n; j++) {
      d[j] = in[j];
      if (!d[j]) q.push(j);
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto j : G[u]) {
        int v = j.first, w = j.second;
        dp[i][v] = (dp[i][u] * w + dp[i][v]) % mod;
        d[v]--;
        if (!d[v] && v < n) q.push(v);
      }
    }
    for (int j = 0; j < n; j++) base.a[i][j] = sb.a[i][j] = dp[i][j + n], sum[i] += dp[i][j];
    sum[i] %= mod;
  }
  for (int i = 0; i < n; i++) {
    sb.a[i + n][i + n] = 1;
    for (int j = 0; j < n; j++)
      sb.a[i][j + n] = sum[j] * dp[i][j + n] % mod;
  }
  ll pl = L / n, pr = R / n;
  mat c = ksm(base, pl, n), t = c;
  if (pl == pr) {
    for (int i = 0; i <= R % n; i++)
      for (int j = L % n; j <= R % n; j++)
        ans += c.a[0][i] * dp[i][j] % mod;
    ans %= mod;
    cout << ans << '\n';
    return;
  }
  for (int i = 0; i < n; i++)
    for (int j = L % n; j < n; j++)
      ans += c.a[0][i] * dp[i][j] % mod;
  ans %= mod;
  t.n = 2 * n;
  t = t * ksm(sb, pr - pl - 1, 2 * n);
  for (int i = 0; i < n; i++) ans += t.a[0][i + n];
  ans %= mod;
  c = ksm(base, pr, n);
  for (int i = 0; i <= R % n; i++)
    for (int j = i; j <= R % n; j++)
      ans += c.a[0][i] * dp[i][j] % mod;
  ans %= mod;
  cout << ans << '\n';
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) work();
  return 0;
}
