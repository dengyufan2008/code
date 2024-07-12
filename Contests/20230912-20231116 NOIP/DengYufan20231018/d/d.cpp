#include <iostream>
#include <vector>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kMaxN = 40001, kMaxM = 10;
int n, m, e[kMaxN][kMaxM], f[kMaxN][kMaxM][1 << kMaxM - 1];
LL ans;
bool b[kMaxM][kMaxM];
char ch;

int PopCount(int x) {
  int c = 0;
  for (; x; x >>= 1) {
    c += x & 1;
  }
  return c;
}

void Update(int &x, int y) {
  x = max(x, y);
}

int R(int x, int s) {
  int ans = 0;
  for (int i = 1; i <= m; i++) {
    ans |= ((e[x][i] & s) > 0) << i - 1;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 1; k <= m; k++) {
        cin >> ch;
        b[j][k] = ch == '1';
      }
    }
    for (int j = 1; j <= m; j++) {
      for (int k = 1; k <= m; k++) {
        e[i][j] |= b[k][j] << k - 1;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      for (int k = 0; k < 1 << m; k++) {
        if (PopCount(k) == m - j) {
          f[i][j][k] = i;
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      for (int k = (1 << m) - 1; k >= 0; k--) {
        if (f[i][j][k]) {
          if (i < n) {
            Update(f[i + 1][j][R(i, k)], f[i][j][k]);
          }
          if (j < m) {
            for (int _k = k, l = _k & -_k; _k; _k ^= l, l = _k & -_k) {
              Update(f[i][j + 1][k ^ l], f[i][j][k]);
            }
          }
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0, p = 1; j <= m; j++) {
      ans += (f[i][j][0] - p + 1) * j;
      p = f[i][j][0] + 1;
    }
  }
  cout << ans - n * m;
  return 0;
}
