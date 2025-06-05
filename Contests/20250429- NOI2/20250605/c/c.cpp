#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const LL kMaxN = 1e5 + 1, kInf = 1e18;
int n, m, a[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  cin >> m;
  for (int i = 1, x, y; i <= m; i++) {
    pair<LL, LL> ans = {kInf, 0};
    cin >> x >> y;
    if (x == y) {
      cout << 0 << ' ' << a[x] << ' ' << 1 << '\n';
      continue;
    }
    for (int j = 0;; j++) {
      for (int k = x; k <= y; k++) {
        int p = 0, q = 0;
        for (int l = x; l < k; l++) {
          if (!p || 1LL * (a[k] - a[p]) * (k - l) > 1LL * (a[k] - a[l]) * (k - p)) {
            p = l;
          }
        }
        for (int l = y; l > k; l--) {
          if (!q || (1LL * j * (a[q] - a[k]) + j - 1) * (l - k) > (1LL * j * (a[l] - a[k]) + j - 1) * (q - k)) {
            q = l;
          }
        }
        LL w1 = p ? 1LL * j * (a[k] - a[p]) / (k - p) : kInf;
        LL w2 = q ? (1LL * j * (a[q] - a[k]) + j - 1) / (q - k) : kInf;
        LL w = min(w1, w2);
        if (1LL * j * a[k] < w * (k - x)) {
          continue;
        }
        bool u = 1;
        for (int l = x; l <= y; l++) {
          LL t = w * (l - k) + 1LL * j * a[k];
          if (t < 1LL * j * a[l] || t >= 1LL * j * (a[l] + 1)) {
            u = 0;
            break;
          }
        }
        if (u) {
          ans = min(ans, {w, 1LL * j * a[k] - w * (k - x)});
        }
      }
      if (ans.first != kInf) {
        cout << ans.first << ' ' << ans.second << ' ' << j << '\n';
        break;
      }
    }
  }
  return 0;
}
