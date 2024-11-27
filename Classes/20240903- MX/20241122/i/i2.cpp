#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

// const int kMaxN = 3e4 + 1, kMaxM = 15, kMod = 998244353;
const int kMaxN = 12 + 1, kMaxM = 10, kMod = 998244353;
int n, m, q, a[kMaxN];
LL f[kMaxM][kMaxN][1 << kMaxM];

LL Ask() {  // O(nm4^m)
  static LL h[1 << kMaxM] = {};
  for (int i = m - 1; i >= 0; i--) {
    for (int l = 1, r = 1; l <= n; l = r) {
      for (; r <= n && (a[l] >= i) == (a[r] >= i); r++) {
      }
      if (a[l] >= i) {
        LL *g = f[i][l];
        g[0] = 1;
        for (int j = 1; j < 1 << i + 1; j++) {
          g[j] = 0;
        }
        for (int p = l, q = l; p < r; p = q) {
          for (; q < r && (a[p] > i) == (a[q] > i); q++) {
          }
          if (a[p] > i) {
            for (int j = 0; j < 1 << i + 1; j++) {
              for (int k = 0; k < 1 << i + 1; k++) {
                h[j ^ k] = (h[j ^ k] + g[j] * f[i + 1][p][k]) % kMod;
              }
            }
            for (int j = 0; j < 1 << i + 1; j++) {
              g[j] = h[j], h[j] = 0;
            }
          } else {
            for (int j = p + (p > l); j < q + (r <= n && q == r); j++) {
              for (int k = 0; k < 1 << i + 1; k++) {
                for (int o = 0; o <= i; o++) {
                  h[k ^ 1 << o] = (h[k ^ 1 << o] + g[k]) % kMod;
                }
              }
              for (int k = 0; k < 1 << i + 1; k++) {
                g[k] = h[k], h[k] = 0;
              }
            }
          }
        }
        if (r <= n) {
          for (int j = 1 << i; j < 1 << i + 1; j++) {
            g[j] = 0;
          }
        } else {
          for (int j = 1 << i; j < 1 << i + 1; j++) {
            g[j & (1 << i) - 1] = (g[j & (1 << i) - 1] + g[j]) % kMod;
            g[j] = 0;
          }
        }
      }
    }
  }
  for (int i = 0; i < m; i++) {
    for (int l = 1, r = 1; l <= n; l++) {
      for (; r <= n && (a[l] >= i) == (a[r] >= i); r++) {
      }
      if (a[l] >= i) {
        cout << i << ' ' << l << '\n';
        for (int j = 0; j <= i; j++) {
          for (int s = 0; s < 1 << i; s++) {
            if (__builtin_popcount(s) == j) {
              cout << f[i][l][s] << " \n"[j == i];
              break;
            }
          }
        }
        cout << '\n';
      }
    }
  }
  return f[0][1][0];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], a[i]--;
  }
  for (int i = 1, x, y; i <= q; i++) {
    cin >> x >> y, y--;
    a[x] = y;
    cout << Ask() << '\n';
  }
  return 0;
}
