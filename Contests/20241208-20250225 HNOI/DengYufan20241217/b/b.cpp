#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 6001, kMod = 998244353;
int n, m, p;
LL ans, f[kMaxN], g[kMaxN], d[kMaxN];  // 没有线/一边的线可以贴着边界
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s >> m, n = s.size() + m;
  for (int i = 1; i <= n; i++) {
    f[i] = 1;
    for (int j = 2; j < i; j++) {
      f[i] = (f[i] + f[i - j] * d[j - 1]) % kMod;
    }
    g[i] = f[i];
    for (int j = 1; j < i && j <= m; j++) {
      g[i] = (g[i] + g[j] * f[i - j]) % kMod;
    }
    d[i] = i <= m ? (d[i - 1] + f[i]) % kMod : d[i - 1];
  }
  for (int i = 1; i < s.size(); i++) {
    if (s[i - 1] != s[i]) {
      if (s[i - 1] == 'R' && s[i] == 'S' ||
          s[i - 1] == 'S' && s[i] == 'P' ||
          s[i - 1] == 'P' && s[i] == 'R') {
        if (i <= p) {
          cout << 0 << '\n';
          return 0;
        } else if (p == 0) {
          ans = g[i - p];
        } else {
          ans = ans * f[i - p] % kMod;
        }
        p = i;
      } else {
        if (i + m <= p) {
          cout << 0 << '\n';
          return 0;
        } else if (p == 0) {
          ans = g[i + m - p];
        } else {
          ans = ans * f[i + m - p] % kMod;
        }
        p = i + m;
      }
    }
  }
  ans = ans * g[n - p] % kMod;
  if (!ans) {
    ans = (g[n] * 2 - f[n] + kMod) % kMod;
    for (int i = 1; i < n && i <= m; i++) {
      for (int j = n - 1; j > i && n - j <= m; j--) {
        ans = (ans + g[i] * g[n - j] % kMod * f[j - i]) % kMod;
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
