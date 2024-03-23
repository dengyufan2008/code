#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const LL kMaxN = 201, kMaxV = 101, kMod = 1e9 + 7;
LL n, ans, a[kMaxN], b[kMaxN], gcd[kMaxV][kMaxV], f[2][kMaxV][kMaxV][kMaxV], t[2][kMaxV][kMaxV][kMaxV];

LL Gcd(LL x, LL y) { return y ? Gcd(y, x % y) : x; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
  }
  for (LL i = 1; i < kMaxV; i++) {
    for (LL j = 1; j < kMaxV; j++) {
      gcd[i][j] = Gcd(i, j);
    }
  }
  for (LL i = a[3]; i <= b[3]; i++) {
    for (LL j = a[2]; j <= b[2]; j++) {
      for (LL k = a[1]; k <= b[1]; k++) {
        t[1][i][gcd[i][j]][gcd[gcd[i][j]][k]] = 3;
        f[1][i][gcd[i][j]][gcd[gcd[i][j]][k]]++;
      }
    }
  }
  for (LL o = 3; o < n; o++) {
    for (LL l = a[o + 1]; l <= b[o + 1]; l++) {
      for (LL k = 1; k <= b[o - 2]; k++) {
        for (LL j = k; j <= b[o - 1]; j += k) {
          for (LL i = ((a[o] - 1) / j + 1) * j; i <= b[o]; i += j) {
            if (t[o & 1][i][j][k] == o) {
              if (t[o & 1 ^ 1][l][gcd[l][i]][gcd[l][j]] <= o) {
                t[o & 1 ^ 1][l][gcd[l][i]][gcd[l][j]] = o + 1;
                f[o & 1 ^ 1][l][gcd[l][i]][gcd[l][j]] = 0;
              }
              f[o & 1 ^ 1][l][gcd[l][i]][gcd[l][j]] = (f[o & 1 ^ 1][l][gcd[l][i]][gcd[l][j]] +
                                                       f[o & 1][i][j][k] * (gcd[l][k] + 1)) %
                                                      kMod;
            }
          }
        }
      }
    }
  }
  for (LL i = 1; i < kMaxV; i++) {
    for (LL j = 1; j < kMaxV; j++) {
      for (LL k = 1; k < kMaxV; k++) {
        if (t[n & 1][i][j][k] == n) {
          ans = (ans + f[n & 1][i][j][k]) % kMod;
        }
      }
    }
  }
  cout << ans;
  return 0;
}
// 为什么扩散能做收集不能做？
// 本质不是扩散与收集. 状态的每一维都要与拓扑序上的那个元素相关. 否则无法转移.
