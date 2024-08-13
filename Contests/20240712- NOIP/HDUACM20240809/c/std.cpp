//
// Created by Luhao Yan on 2024/7/23.
//

#include <bits/stdc++.h>

using ll = long long;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;
const int base = 40;
int dp[42][32][82][32][32];
int norm(int x) {
  return x >= mod ? x - mod : x;
}

void solve() {
  int n, m;
  std::cin >> n >> m;
  std::string s;
  std::cin >> s;
  int k = (int)s.length();
  s = ' ' + s;
  std::vector nxt(k + 1, -1);
  std::vector tr(k + 1, std::array<int, 2>());
  for (int i = 1; i <= k; ++i) {
    int j = nxt[i - 1];
    while (j != -1 && s[j + 1] != s[i]) j = nxt[j];
    nxt[i] = j + 1;
  }
  for (int i = 0; i < k; ++i) {
    for (int c = 0; c < 2; ++c) {
      if (i < k and (s[i + 1] == 'R') == c)
        tr[i][c] = i + 1;
      else
        tr[i][c] = (i != 0 ? tr[nxt[i]][c] : 0);
    }
  }
  int ans = 0;
  for (int i = 0; i < k; ++i) {
    memset(dp, 0, sizeof dp);
    dp[1][i][0 + base][0][0] = 1;
    for (int j = 1; j <= m; ++j) {
      for (int u = 0; u < k; ++u) {
        for (int sm = -j; sm <= j and sm <= n; ++sm)
          for (int pr = std::max(0, sm); pr <= j and pr <= n; ++pr)
            for (int sf = std::max(0, sm); sf <= j and sf <= n; ++sf) {
              if (not dp[j][u][sm + base][pr][sf]) continue;
              for (int c = 0; c < 2; ++c) {
                int v = tr[u][c];
                if (v == k) continue;
                assert(0 <= v and v <= k);
                int w = (c == 0 ? -1 : 1);
                int ns = sm + w;
                int np = std::max(pr, ns);
                int nsf = std::max(0, sf + w);
                if (nsf >= n) continue;
                dp[j + 1][v][ns + base][np][nsf] =
                    norm(dp[j + 1][v][ns + base][np][nsf] +
                         dp[j][u][sm + base][pr][sf]);
              }
            }
      }
    }
    for (int sm = -m; sm <= 0; ++sm)
      for (int pr = 0; pr <= std::min(n, m); ++pr)
        for (int sf = 0; sf <= std::min(n, m); ++sf) {
          if (pr + sf >= n) continue;
          if (not dp[m + 1][i][sm + base][pr][sf]) continue;
          ans = (ans + (ll)dp[m + 1][i][sm + base][pr][sf] * (n - pr)) % mod;
        }
  }
  for (int i = 1; i <= m; ++i)
    ans = (ll)ans * inv2 % mod;
  std::cout << ans << '\n';
}

int main() {
  freopen("c.in", "r", stdin);
  freopen("c.ans", "w", stdout);
  int t;
  std::cin >> t;
  while (t-- > 0) solve();
  return 0;
}
