#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define MOD 1000000007
#define mod 998244353
#define F first
#define S second
#define ll long long
#define N 50
#define M 50000
using namespace std;
ll ksm(ll x, ll y) {
  ll ret = 1;
  while (y > 0) {
    if (y & 1) {
      ret = (ret * x) % mod;
    }
    x = (x * x) % mod;
    y >>= 1;
  }
  return ret;
}
ll n, m, H, W, C[N][N], coefr[N], coefc[N], idx[(1 << 18) + 10], dp[10][M];
vector<ll> allmask;
vector<pair<ll, ll> > vt[M][10];
void dfs(vector<ll> v, ll x, ll s, ll w, ll id) {
  ll i;
  if (x < 0) {
    ll mask = 0;
    for (i = 0; i < v.size(); i++) {
      mask |= 1 << (i + v[i]);
    }
    vt[id][s].push_back(make_pair(idx[mask], w));
    return;
  }
  for (i = x - 1; i >= 0; i--) {
    if (v[i] != v[x]) {
      break;
    }
  }
  ll len = x - i;
  for (i = x; i >= x - len; i--) {
    dfs(v, x - len, s, w * C[len][x - i], id);
    if (i == x - len) {
      break;
    }
    v[i]++, s++;
  }
  return;
}
void init(ll mask) {
  ll i, j;
  vector<ll> v;
  for (i = j = 0; i < n + m; i++) {
    if ((mask >> i) & 1) {
      v.push_back(j);
    } else {
      j++;
    }
  }
  if (v.back() == m) {
    return;
  }
  dfs(v, v.size() - 1, 0, 1, idx[mask]);
  return;
}
int main() {
  freopen("map.in", "r", stdin);
  freopen("map.ans", "w", stdout);
  ll i, j, k, l;
  cin >> n >> m >> H >> W;
  for (i = 0; i < N; i++) {
    C[i][0] = 1;
    for (j = 1; j <= i; j++) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
  }
  for (i = 0; i <= m; i++) {
    for (j = 0; j <= i; j++) {
      coefr[i] = (coefr[i] + ksm(C[i][j], H / n)) % mod;
    }
    for (j = 0; j < i; j++) {
      coefr[i] = (coefr[i] + mod - ((coefr[j] * ((C[i][j] * (1 << (i - j))) % mod)) % mod)) % mod;
    }
  }
  for (i = 0; i <= n; i++) {
    for (j = 0; j <= i; j++) {
      coefc[i] = (coefc[i] + ksm(C[i][j], W / m)) % mod;
    }
  }
  for (i = 0; i < (1 << (n + m)); i++) {
    idx[i] = -1;
    if (__builtin_popcount(i) == n) {
      idx[i] = allmask.size();
      allmask.push_back(i);
    }
  }
  for (i = 0; i < allmask.size(); i++) {
    init(allmask[i]);
  }
  dp[0][idx[(1 << n) - 1]] = 1;
  for (i = 0; i < m; i++) {
    for (j = 0; j < allmask.size(); j++) {
      if (!dp[i][j]) {
        continue;
      }
      dp[i][j] %= mod;
      for (k = 0; k <= n; k++) {
        for (l = 0; l < vt[j][k].size(); l++) {
          dp[i + 1][vt[j][k][l].F] += ((dp[i][j] * coefc[n - k]) % mod) * vt[j][k][l].S;
        }
      }
    }
  }
  ll ans = 0;
  for (i = 0; i < allmask.size(); i++) {
    dp[m][i] %= mod;
    if (!dp[m][i]) {
      continue;
    }
    ll coef = 1;
    for (j = k = 0; j < n + m; j++) {
      if ((allmask[i] >> j) & 1) {
        coef = (coef * coefr[k]) % mod;
      } else {
        k++;
      }
    }
    ans = (ans + dp[m][i] * coef) % mod;
  }
  cout << ans << '\n';
  return 0;
}
