#include <fstream>

using namespace std;

ifstream cin("mex.in");
ofstream cout("mex.out");

const int kMaxN = 151, kMaxM = 17;
int n, ans, a[kMaxN], lg[1 << kMaxM];
int p[kMaxN][kMaxM], f[1 << kMaxM], g[kMaxN][kMaxM];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < kMaxM; i++) {
    p[n][i] = g[n][i] = n + 1, lg[1 << i] = i;
  }
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j < kMaxM; j++) {
      p[i][j] = p[i + 1][j];
    }
    if (a[i + 1] < kMaxM) {
      p[i][a[i + 1]] = i + 1;
    }
    g[i][0] = a[i + 1] ? i + 1 : g[i + 1][0];
    for (int j = 1, x = 0; j < kMaxM; j++) {
      x = max(x, p[i][j - 1]);
      g[i][j] = g[i + 1][j];
      if (x < p[i][j]) {
        g[i][j] = min(g[i][j], x);
      }
    }
  }
  for (int s = 1; s < 1 << kMaxM; s++) {
    f[s] = n + 1;
  }
  for (int s = 0; s + 1 < 1 << kMaxM; s++) {
    if (f[s] < n) {
      for (int t = s ^ (1 << kMaxM) - 1; t; t &= t - 1) {
        int i = lg[t & -t];
        f[s | 1 << i] = min(f[s | 1 << i], g[f[s]][i]);
      }
    }
  }
  for (int s = 0; s < 1 << kMaxM; s++) {
    if (f[s] <= n) {
      int t = s ^ (1 << kMaxM) - 1;
      ans = max(ans, t ? lg[t & -t] : kMaxM);
    }
  }
  cout << ans << '\n';
  return 0;
}
