// #include <fstream>
#include <iostream>

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 1e6 + 2;
int n, m, f[kMaxN][2][2], g[kMaxN][2][2];
string s, t;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> s;
  s = '~' + s;
  if ((m & 1) && s[1] == s[n] && s[1] != '?' && s[n] != '?' || !(m & 1) && s[1] != s[n] && s[1] != '?' && s[n] != '?') {
    cout << -1;
    return 0;
  }
  if (s[n] != '1') {
    f[n][0][0] = 0, f[n][0][1] = -n;
    g[n][0][0] = 0, g[n][0][1] = n;
  } else {
    f[n][0][0] = f[n][0][1] = -n;
    g[n][0][0] = g[n][0][1] = n;
  }
  if (s[n] != '0') {
    f[n][1][0] = 0, f[n][1][1] = -n;
    g[n][1][0] = 0, g[n][1][1] = n;
  } else {
    f[n][1][0] = f[n][1][1] = -n;
    g[n][1][0] = g[n][1][1] = n;
  }
  for (int i = n - 1; i >= 1; i--) {
    if (s[i] != '1') {
      f[i][0][0] = max(f[i + 1][0][0], f[i + 1][1][1] + 1);
      f[i][0][1] = max(f[i + 1][0][1], f[i + 1][1][0] + 1);
      g[i][0][0] = min(g[i + 1][0][0], g[i + 1][1][1] + 1);
      g[i][0][1] = min(g[i + 1][0][1], g[i + 1][1][0] + 1);
    } else {
      f[i][0][0] = f[i][0][1] = -n;
      g[i][0][0] = g[i][0][1] = n;
    }
    if (s[i] != '0') {
      f[i][1][0] = max(f[i + 1][0][1] + 1, f[i + 1][1][0]);
      f[i][1][1] = max(f[i + 1][0][0] + 1, f[i + 1][1][1]);
      g[i][1][0] = min(g[i + 1][0][1] + 1, g[i + 1][1][0]);
      g[i][1][1] = min(g[i + 1][0][0] + 1, g[i + 1][1][1]);
    } else {
      f[i][1][0] = f[i][1][1] = -n;
      g[i][1][0] = g[i][1][1] = n;
    }
  }
  for (int i = 1, p; i <= n; i++) {
    if (f[i][0][m - (i != 1 && p == 1) & 1] >= m - (i != 1 && p == 1) && g[i][0][m - (i != 1 && p == 1) & 1] <= m - (i != 1 && p == 1)) {
      t += '0', m -= i != 1 && p == 1, p = 0;
    } else if (f[i][1][m - (i != 1 && p == 0) & 1] >= m - (i != 1 && p == 0) && g[i][1][m - (i != 1 && p == 0) & 1] <= m - (i != 1 && p == 0)) {
      t += '1', m -= i != 1 && p == 0, p = 1;
    } else {
      cout << -1;
      return 0;
    }
  }
  cout << t;
  return 0;
}
