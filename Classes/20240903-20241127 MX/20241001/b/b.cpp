#include <fstream>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 101, kMaxV = 1e9 + 1;
int t, n, a[kMaxN], f[kMaxN][kMaxN], g[kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
      f[i][i] = g[i][i] = 1;
    }
    for (int i = 2; i <= n; i++) {
      for (int l = 1, r; (r = l + i - 1) <= n; l++) {
        if (a[r] < g[l + 1][r]) {
          f[l][r] = 1;
        } else {
          f[l][r] = min(a[r] - g[l + 1][r] + f[l][r - 1] + 1, kMaxV);
        }
        if (a[l] < f[l][r - 1]) {
          g[l][r] = 1;
        } else {
          g[l][r] = min(a[l] - f[l][r - 1] + g[l + 1][r] + 1, kMaxV);
        }
      }
    }
    cout << (f[1][n] <= a[1] ? "First\n" : "Second\n");
  }
  return 0;
}
