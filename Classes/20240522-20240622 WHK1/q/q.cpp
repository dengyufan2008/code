#include <fstream>

using namespace std;

ifstream cin("q.in");
ofstream cout("q.out");

const int kMaxN = 202, kMaxM = kMaxN << 1, kMod = 1e4 + 7;
int n, m, _n, _m, ans, f[kMaxN][kMaxN][kMaxN], g[kMaxM][kMaxM], d[kMaxM][kMaxM];
string s;

void Add(int &x, int y) { x = (x + y) % kMod; }

void Mul(int a[kMaxM][kMaxM], int b[kMaxM][kMaxM]) {
  static int c[kMaxM][kMaxM] = {};
  for (int i = 0; i <= _m; i++) {
    for (int j = 0; j <= _m; j++) {
      c[i][j] = 0;
      // for (int k = 0; k <= _m; k++) {
      //   c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % kMod;
      // }
      int l = 0, r = _m, mid = m + 1;
      if (i <= m) {
        l = max(l, i);
      } else {
        l = max(l, m + 1), r = min(r, i);
      }
      if (j <= m) {
        r = min(r, j);
      } else {
        mid = max(mid, j);
      }
      if (l >= mid || r <= m) {
        for (int k = l; k <= r; k++) {
          c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % kMod;
        }
      } else {
        for (int k = l; k <= m; k++) {
          c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % kMod;
        }
        for (int k = mid; k <= r; k++) {
          c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % kMod;
        }
      }
    }
  }
  for (int i = 0; i <= _m; i++) {
    for (int j = 0; j <= _m; j++) {
      b[i][j] = c[i][j];
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s >> n, m = s.size(), s = '~' + s;
  n += m, _m = m + (m + 1 >> 1) + 1, f[1][m][0] = 1;
  for (int i = m; i >= 1; i--) {
    for (int l = 1, r; (r = l + i - 1) <= m; l++) {
      for (int j = m - r + l - 1; j >= 0; j -= 2) {
        if (s[l] == s[r]) {
          Add(f[l + 1][r - 1][j], f[l][r][j]);
        } else {
          Add(f[l][r - 1][j + 1], f[l][r][j]);
          Add(f[l + 1][r][j + 1], f[l][r][j]);
        }
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    d[i][i] = 24, d[i + m + 1][i + m + 1] = 25;
    d[i - 1][i] = d[i + m + 1][i + m] = 1;
  }
  d[m + 1][m + 1] = 26, g[m + 1][m + 1] = 1;
  for (int i = 1; i <= m; i++) {  // [i+1, i-1]
    for (int j = m + 1, k = 0; j >= 0; j -= 2, k++) {
      Add(d[j][k + m + 1], f[i + 1][i - 1][j]);
    }
  }
  _n = n + 3 >> 1;
  for (int i = 1; i <= _n; i <<= 1) {
    if (i & _n) {
      Mul(d, g);
    }
    Mul(d, d);
  }
  Add(ans, g[0][m + 1]);
  for (int i = 0; i <= m + m + 1; i++) {
    for (int j = 0; j <= m + m + 1; j++) {
      g[i][j] = d[i][j] = 0;
    }
  }
  for (int i = 1; i <= m; i++) {
    d[i][i] = 24, d[i + m + 1][i + m + 1] = 25;
    d[i - 1][i] = d[i + m + 1][i + m] = 1;
  }
  d[m + 1][m + 1] = 26, g[m + 1][m + 1] = n & 1 ? 26 : 1;
  for (int i = 1; i <= m + 1; i++) {  // [i, i-1]
    for (int j = m, k = 0; j >= 0; j -= 2, k++) {
      Add(d[j][k + m + 1], f[i][i - 1][j]);
    }
  }
  _n = n + 2 >> 1;
  for (int i = 1; i <= _n; i <<= 1) {
    if (_n & i) {
      Mul(d, g);
    }
    Mul(d, d);
  }
  Add(ans, g[0][m + 1]);
  cout << ans << '\n';
  return 0;
}
