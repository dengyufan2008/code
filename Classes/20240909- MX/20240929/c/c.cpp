#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1001, kInf = 1e9;
int n, x, y, ans[2], a[2][kMaxN][kMaxN];
int f[2][kMaxN][kMaxN], g[2][kMaxN][kMaxN];

int Calc(bool o) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == 1 && j == 1) {
        f[o][i][j] = a[o][i][j], g[o][i][j] = a[o ^ 1][i][j];
        continue;
      }
      int f0 = i > 1 ? f[o][i - 1][j] + a[o][i][j] : kInf;
      int f1 = j > 1 ? f[o][i][j - 1] + a[o][i][j] : kInf;
      f[o][i][j] = min(min(f0, f1), kInf), g[o][i][j] = kInf;
      if (f[o][i][j] == f0) {
        g[o][i][j] = min(g[o][i][j], g[o][i - 1][j] + a[o ^ 1][i][j]);
      }
      if (f[o][i][j] == f1) {
        g[o][i][j] = min(g[o][i][j], g[o][i][j - 1] + a[o ^ 1][i][j]);
      }
    }
  }
  return min(f[o][n][n], g[o][n][n]);
}

void Print(int n, int m, bool o) {
  if (n > 1) {
    if (f[o][n - 1][m] + a[o][n][m] == f[o][n][m]) {
      if (g[o][n - 1][m] + a[o ^ 1][n][m] == g[o][n][m]) {
        Print(n - 1, m, o), cout << 'D';
        return;
      }
    }
  }
  if (m > 1) {
    Print(n, m - 1, o), cout << 'R';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      static int w;
      cin >> w;
      if (w) {
        for (; !(w % 2); w /= 2) {
          a[0][i][j]++;
        }
        for (; !(w % 5); w /= 5) {
          a[1][i][j]++;
        }
      } else {
        x = i, y = j, a[0][i][j] = a[1][i][j] = kInf;
      }
    }
  }
  ans[0] = Calc(0), ans[1] = Calc(1);
  if (!x || !min(ans[0], ans[1])) {
    cout << min(ans[0], ans[1]) << '\n';
    Print(n, n, ans[0] > ans[1]), cout << '\n';
  } else {
    cout << 1 << '\n';
    cout << string(x - 1, 'D') << string(y - 1, 'R');
    cout << string(n - x, 'D') << string(n - y, 'D');
    cout << '\n';
  }
  return 0;
}
