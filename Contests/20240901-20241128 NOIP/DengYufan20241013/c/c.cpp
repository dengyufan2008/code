#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1e5 + 2, kInf = 1e9;
const int kMaxL = 17, kMaxM = kMaxL * kMaxL;
struct L {
  int d, m;
} l[kMaxM];
int n, m, ans, a[kMaxN], f[kMaxM], g[kMaxM];
int h[kMaxN][kMaxL], w[kMaxN][kMaxL], d[kMaxL];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n, a[0] = 1;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], m = max(m, a[i]);
  }
  for (int i = 1 - kMaxL; i < kMaxL; i++) {
    for (int j = kMaxL - max(0, i) - 1; j >= max(0, -i); j--) {
      static int o = 0;
      l[o++] = {j, i + j};
    }
  }
  for (int i = 0; i < kMaxL; i++) {
    h[n][i] = kInf;
  }
  for (int i = 0, x = a[n]; x; i++, x >>= 1) {
    int c = 0;
    for (int &y = w[n][i] = x; y <= m; y <<= 1, c++) {
    }
    h[n][i] = c + i;
  }
  for (int i = n - 1; i >= 1; i--) {
    for (int j = 0; j < kMaxL; j++) {
      h[i][j] = kInf;
    }
    for (int j = 0, x = a[i]; x; j++, x >>= 1) {
      int c = 0;
      for (int &y = w[i][j] = x; y <= m; y <<= 1, c++) {
      }
      for (int k = 0; k < kMaxL && w[i + 1][k]; k++) {
        if (w[i][j] <= w[i + 1][k]) {
          h[i][j] = min(h[i][j], h[i + 1][k]);
        } else {
          h[i][j] = min(h[i][j], h[i + 1][k] + n - i);
        }
      }
      h[i][j] += c + j;
    }
  }
  ans = kInf;
  for (int i = 0; i < kMaxL; i++) {
    ans = min(ans, h[1][i]), d[i] = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < kMaxM; j++) {
      g[j] = f[j];
    }
    int o = kInf;
    for (int j = 0, k = 0; j < kMaxM; j++) {
      for (; k < kMaxM && a[i] >> l[j].d << l[j].m >= a[i - 1] >> l[k].d << l[k].m; k++) {
      }
      f[j] = (k ? g[k - 1] : kInf) + l[j].d + l[j].m;
      o > f[j] ? o = f[j] : f[j] = o;
    }
    int w = kInf;
    for (int j = 0; j < kMaxM; j++) {
      if (a[i] >> l[j].d << l[j].m <= m) {
        w = f[j];
      } else {
        break;
      }
    }
    for (int j = 0; j < kMaxL; j++) {
      ans = min(ans, w + h[i + 1][j]);
    }
  }
  ans = min(ans, f[kMaxM - 1]);
  cout << ans << '\n';
  return 0;
}
