#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream cin("mechanic.in");
ofstream cout("mechanic.out");

const int kMaxN = 502, kMaxV = 1000, kInf = 1e9;
struct A {
  int s, t;
} a[kMaxN];
int n, m;
double ans, f[kMaxN][kMaxN], g[kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].s >> a[i].t;
    a[i].t == -1 && (a[i].t = kMaxV + 1);
  }
  sort(a + 1, a + n + 1, [](A i, A j) {
    return i.t < j.t;
  });
  for (int i = 0; i <= n + 1; i++) {
    for (int j = 0; j <= n + 1; j++) {
      f[i][j] = g[i][j] = kInf;
    }
  }
  f[0][0] = g[n + 1][0] = 0, ans = kInf;
  for (int i = 0; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 0; k <= j; k++) {
        f[j][k] = f[j - 1][k] + (double)a[j].s / (m - i + 1);
        if (k && a[j].t <= kMaxV) {
          f[j][k] = min(f[j][k], f[j - 1][k - 1] + (double)a[j].t / k);
        }
      }
    }
    for (int j = n; j >= 1; j--) {
      for (int k = 0; k <= n - j + 1; k++) {
        g[j][k] = g[j + 1][k];
        if (k) {
          g[j][k] = min(g[j][k], g[j + 1][k - 1] + (double)a[j].s / (m - i + 1));
        }
      }
    }
    for (int j = m - i; j <= m; j++) {
      ans = min(ans, f[j][m - i] + g[j + 1][m - j]);
    }
  }
  cout << fixed << setprecision(10) << ans << '\n';
  return 0;
}
