#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1001, kInf = 1e9;
int n, x, y, a[kMaxN][kMaxN][2];
int f[kMaxN][kMaxN][2];

void Calc() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == 1 && j == 1) {
        f[i][j][0] = a[i][j][0], f[i][j][1] = a[i][j][1];
        continue;
      }
      static int f0, f1;
      f0 = i > 1 ? f[i - 1][j][0] + a[i][j][0] : kInf;
      f1 = j > 1 ? f[i][j - 1][0] + a[i][j][0] : kInf;
      f[i][j][0] = min(min(f0, f1), kInf);
      f0 = i > 1 ? f[i - 1][j][1] + a[i][j][1] : kInf;
      f1 = j > 1 ? f[i][j - 1][1] + a[i][j][1] : kInf;
      f[i][j][1] = min(min(f0, f1), kInf);
    }
  }
}

void Print(int n, int m, bool o) {
  if (n > 1) {
    if (f[n - 1][m][o] + a[n][m][o] == f[n][m][o]) {
      Print(n - 1, m, o), cout << 'D';
      return;
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
          a[i][j][0]++;
        }
        for (; !(w % 5); w /= 5) {
          a[i][j][1]++;
        }
      } else {
        x = i, y = j, a[i][j][0] = a[i][j][1] = kInf;
      }
    }
  }
  Calc();
  if (!x || !min(f[n][n][0], f[n][n][1])) {
    cout << min(f[n][n][0], f[n][n][1]) << '\n';
    Print(n, n, f[n][n][0] > f[n][n][1]), cout << '\n';
  } else {
    cout << 1 << '\n';
    cout << string(x - 1, 'D') << string(y - 1, 'R');
    cout << string(n - x, 'D') << string(n - y, 'D');
    cout << '\n';
  }
  return 0;
}
