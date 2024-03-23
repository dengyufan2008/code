#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const LL kMaxN = 1e5 + 1, kMaxL = 30, kMod = 1e9 + 7;
LL n, ans, a[kMaxN], p[kMaxN], f[kMaxN][4];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
    p[i] = p[i] * 857142863 % kMod;
  }
  f[0][0] = 1;
  for (int i = 0; i < kMaxL; i++) {
    for (int j = 0; j < kMaxL; j++) {
      for (int k = 1; k <= n; k++) {
        int s = (a[k] >> i & 1) << 1 | (a[k] >> j & 1);
        for (int t = 0; t < 4; t++) {
          f[k][t] = (f[k - 1][t ^ s] * p[k] + f[k - 1][t] * (kMod + 1 - p[k])) % kMod;
        }
      }
      ans = (ans + (1LL << i) * (1LL << j) % kMod * f[n][3] % kMod) % kMod;
    }
  }
  cout << ans;
  return 0;
}
