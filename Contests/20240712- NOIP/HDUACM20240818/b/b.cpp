#include <fstream>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 5001;
struct A {
  int l, r, x;
} a[kMaxN];
int t, n, m, f[kMaxN][kMaxN];
bool ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].l >> a[i].r >> a[i].x;
    }
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= m; j++) {
        f[i][j] = n + 1;
      }
    }
    f[a[n].l][a[n].r] = n;
    for (int i = m; i >= 1; i--) {
      for (int j = 1, k; (k = j + i - 1) <= m; j++) {
        int w = f[j][k], l, r;
        if (w >= 1 && w <= n && a[w].x <= i) {
          if (w == 1) {
            ans = 1;
          } else {
            l = max(j + a[w].x, a[w - 1].l);
            r = min(k, a[w - 1].r);
            if (l <= r) {
              f[l][r] = min(f[l][r], w - 1);
            }
            l = max(j, a[w - 1].l);
            r = min(k - a[w].x, a[w - 1].r);
            if (l <= r) {
              f[l][r] = min(f[l][r], w - 1);
            }
          }
        }
      }
    }
    cout << (ans ? "YES\n" : "NO\n"), ans = 0;
  }
  return 0;
}
