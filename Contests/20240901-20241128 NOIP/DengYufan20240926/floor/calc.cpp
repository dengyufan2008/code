#include <fstream>
#define LL long long

using namespace std;

ifstream cin("floor.ans");
ofstream cout("floor.out");

const int kMaxN = 11, kMaxM = 6, kMod = 998244353;
int n, m, a[kMaxN][kMaxN], o[kMaxM][kMaxM];
LL d[kMaxN * kMaxN][kMaxM * kMaxM];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 1; i < kMaxN; i++) {
    for (int j = 1; j < kMaxN; j++) {
      cin >> a[i][j];
    }
  }
  for (int p = 0; p <= 5; p++) {
    for (int q = 0; q <= 5; q++) {
      if (p + q <= 5) {
        o[p][q] = ++m;
      }
    }
  }
  for (int i = 1; i < kMaxN; i++) {
    for (int j = 1; j < kMaxN; j++) {
      d[++n][m + 1] = a[i][j];
      for (int p = 0; p <= 5; p++) {
        for (int q = 0; q <= 5; q++) {
          if (p + q <= 5) {
            d[n][o[p][q]] = Pow(i, p) * Pow(j, q);
          }
        }
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    if (!d[i][i]) {
      for (int j = i + 1; j <= n; j++) {
        if (d[j][i]) {
          swap(d[i], d[j]);
          break;
        }
      }
    }
    LL inv = Pow(d[i][i]);
    for (int j = m + 1; j >= i; j--) {
      d[i][j] = d[i][j] * inv % kMod;
    }
    for (int j = i + 1; j <= n; j++) {
      if (d[j][i]) {
        for (int k = m + 1; k >= i; k--) {
          d[j][k] = (d[j][k] - d[j][i] * d[i][k]) % kMod;
        }
      }
    }
  }
  for (int i = m; i >= 1; i--) {
    for (int j = i - 1; j >= 1; j--) {
      d[j][m + 1] = (d[j][m + 1] - d[i][m + 1] * d[j][i]) % kMod;
      d[j][i] = 0;
    }
  }
  for (int i = 1; i < m; i++) {
    cout << (d[i][m + 1] + kMod) % kMod << ", ";
  }
  cout << (d[m][m + 1] + kMod) % kMod << '\n';
  return 0;
}
