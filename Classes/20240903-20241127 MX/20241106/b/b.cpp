#include <fstream>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1001, kMaxM = 1 << 13 | 1;
int t, n, m, a[kMaxN], f[kMaxN][kMaxM], high[kMaxM];

void Print(int n, int m) {
  if (n) {
    if (f[n][m] >= kMaxM) {
      Print(n - 1, f[n][m] - kMaxM), cout << 'l';
    } else {
      Print(n - 1, f[n][m]), cout << 'r';
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 1; i < kMaxM; i++) {
    f[0][i] = -1, high[i] = 1;
    for (int x = i >> 1; x; x >>= 1) {
      high[i] <<= 1;
    }
  }
  cin >> t;
  while (t--) {
    cin >> n, m = 0, f[0][0] = 0;
    for (int i = 1, x; i <= n; i++) {
      cin >> x, a[i] = x;
      for (int j = 0; j <= m + x; j++) {
        f[i][j] = -1;
      }
      for (int j = 0; j <= m; j++) {
        if (~f[i - 1][j]) {
          if (!j || x <= (j & -j)) {
            f[i][j + x] = j + kMaxM;
          }
          if (j && j == m && high[j] >= x || x <= (m - j & j - m)) {
            if (high[m - j + x] == m - j + x && high[j] == m - j + x) {
              f[i][m + x] = j;
            } else {
              f[i][j] = j;
            }
          } else if (j && j == m) {
            f[i][j + x] = j;
          }
        }
      }
      m += x;
    }
    if (~f[n][m] && high[m] == m) {
      Print(n, m), cout << '\n';
    } else {
      cout << "no\n";
    }
  }
  return 0;
}
