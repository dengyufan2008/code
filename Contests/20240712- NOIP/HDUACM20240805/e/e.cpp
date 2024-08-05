// by lsl
#include <bits/stdc++.h>
using namespace std;
const int N = 6e4 + 5, M = 15;
int dp[2][N];
char c[M];
// 0 green
// 1 yellow
// 2 red
int ch(int x, char p) {
  if (p == '0') return x;
  if (p == '+') return (x + 1) % 3;
  if (p == '-') return (x + 2) % 3;
}
int n, k, mod;
int pw[M];
int T;
vector<pair<string, int>> out;
void work() {
  memset(dp, -1, sizeof(dp));
  out.clear();
  cin >> n >> k >> mod;
  int o = 0;
  dp[o][0] = 1;
  for (int i = 1; i <= n; i++) {
    o ^= 1;
    memset(dp[o], -1, sizeof(dp[o]));
    cin >> c;
    for (int j = 0; j < pw[k]; j++) {
      if (dp[o ^ 1][j] < 0) continue;
      int res = 0;
      for (int l = 0; l < k; l++) res += ch(j / pw[l] % 3, c[l]) * pw[l];
      dp[o][j] = ((dp[o][j] < 0 ? 0 : dp[o][j]) + dp[o ^ 1][j]) % mod;
      dp[o][res] = ((dp[o][res] < 0 ? 0 : dp[o][res]) + dp[o ^ 1][j]) % mod;
    }
  }
  for (int j = 0; j < pw[k]; j++) {
    if (dp[o][j] < 0) continue;
    string s;
    for (int l = 0; l < k; l++) s += 'A' + j / pw[l] % 3;
    out.push_back(make_pair(s, dp[o][j]));
  }
  sort(out.begin(), out.end());
  for (auto i : out) cout << i.first << ' ' << i.second << '\n';
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  pw[0] = 1;
  for (int i = 1; i <= 10; i++) pw[i] = pw[i - 1] * 3;
  cin >> T;
  while (T--) work();
}
