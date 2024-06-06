#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.ans");

const int kMaxN = 10001, kInf = 1e9;
int o, n, m, k, f[kMaxN][kMaxN];
string s, t;

int Print(int n, int m, int x) {
  if (x <= 0) {
    return n + 1;
  } else if (m && f[n][m - 1] == x - 1) {
    int w = Print(n, m - 1, x - 1);
    cout << "INSERT " << w << ' ' << t[m] << '\n';
    return w + 1;
  } else if (n && f[n - 1][m] == x - 1) {
    int w = Print(n - 1, m, x - 1);
    cout << "DELETE " << w << '\n';
    return w;
  } else if (s[n] != t[m]) {
    int w = Print(n - 1, m - 1, x - 1);
    cout << "REPLACE " << w << ' ' << t[m] << '\n';
    return w + 1;
  }
  return Print(n - 1, m - 1, x) + 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> n >> m >> k >> s >> t;
    s = '~' + s, t = '~' + t;
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        f[i][j] = i || j ? kInf : 0;
        if (i) {
          f[i][j] = min(f[i][j], f[i - 1][j] + 1);
        }
        if (j) {
          f[i][j] = min(f[i][j], f[i][j - 1] + 1);
        }
        if (i && j) {
          f[i][j] = min(f[i][j], f[i - 1][j - 1] + (s[i] != t[j]));
        }
      }
    }
    if (f[n][m] <= k) {
      cout << "YES\n"
           << f[n][m] << '\n';
      Print(n, m, f[n][m]);
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
