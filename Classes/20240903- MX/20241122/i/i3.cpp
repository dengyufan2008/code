#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 3e4 + 1, kMaxM = 15 + 1, kMod = 998244353, kInv2 = kMod + 1 >> 1;
int n, m, q, a[kMaxN];
LL f[kMaxM - 1][kMaxN][kMaxM];
int fwt[kMaxM][kMaxM][kMaxM], inv[kMaxM];

void Init() {  // O(m^4)
  static LL c[kMaxM][kMaxM] = {};
  for (int i = 0; i <= m; i++) {
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; j++) {
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % kMod;
    }
  }
  inv[0] = fwt[0][0][0] = 1;
  for (int i = 1; i <= m; i++) {
    inv[i] = 1LL * inv[i - 1] * kInv2 % kMod;
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k <= i; k++) {
        for (int l = max(j + k - i, 0); l <= min(j, k); l++) {
          LL w = c[j][l] * c[i - j][k - l] % kMod;
          if (l & 1) {
            fwt[i][j][k] = (fwt[i][j][k] - w + kMod) % kMod;
          } else {
            fwt[i][j][k] = (fwt[i][j][k] + w) % kMod;
          }
        }
      }
    }
  }
}

LL Ask() {  // O(nm^3)
  static LL h[kMaxM] = {};
  for (int i = m - 1; i >= 0; i--) {
    for (int l = 1, r = 1; l <= n; l = r) {
      for (; r <= n && (a[l] >= i) == (a[r] >= i); r++) {
      }
      if (a[l] >= i) {
        for (int j = 0; j <= i + 1; j++) {
          h[j] = 1;
        }
        int c = (a[l] == i) + (r <= n && a[r - 1] == i);
        for (int p = l, q = l; p < r; p = q) {
          for (; q < r && (a[p] > i) == (a[q] > i); q++) {
          }
          if (a[p] > i) {
            for (int j = 0; j <= i + 1; j++) {
              LL w = 0;
              for (int k = 0; k <= i + 1; k++) {
                w = (w + f[i + 1][p][k] * fwt[i + 1][j][k]) % kMod;
              }
              h[j] = h[j] * w % kMod;
            }
          } else {
            c += q - p - 1;
          }
        }
        LL *g = f[i][l];
        for (int j = 0; j <= i + 1; j++) {
          g[j] = 0;
          for (int k = 0; k <= i + 1; k++) {
            g[j] = (g[j] + h[k] * fwt[i + 1][j][k]) % kMod;
          }
          g[j] = g[j] * inv[i + 1] % kMod;
        }
        for (int j = 0; j < c; j++) {
          for (int k = 0; k <= i + 1; k++) {
            if (k == 0) {
              h[k] = g[k + 1] * (i + 1 - k) % kMod;
            } else if (k == i + 1) {
              h[k] = g[k - 1] * k % kMod;
            } else {
              h[k] = (g[k - 1] * k + g[k + 1] * (i + 1 - k)) % kMod;
            }
          }
          for (int k = 0; k <= i + 1; k++) {
            g[k] = h[k];
          }
        }
        if (r == n + 1) {
          for (int j = 0; j <= i; j++) {
            g[j] = (g[j] + g[j + 1]) % kMod;
          }
          g[i + 1] = 0;
        }
      }
    }
  }
  // cout << '\n';
  // for (int i = 0; i < m; i++) {
  //   for (int j = 1; j <= n; j++) {
  //     for (int k = 0; k <= i; k++) {
  //       cout << f[i][j][k] << " \n"[k == i];
  //     }
  //   }
  //   cout << '\n';
  // }
  return f[0][1][0];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], a[i]--;
  }
  Init();
  for (int i = 1, x, y; i <= q; i++) {
    cin >> x >> y, y--;
    a[x] = y;
    cout << Ask() << '\n';
  }
  return 0;
}
