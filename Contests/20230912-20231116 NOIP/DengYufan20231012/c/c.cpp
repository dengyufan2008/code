#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const LL kMaxN = 4e5 + 1, kInf = 1e9;
LL n, m, ans, f[kMaxN], g[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  m >>= 1;
  for (LL i = 1; i <= min(n, m - 1); i++) {
    f[i] = i + 2;
  }
  for (LL i = min(n, m - 1) + 1; i < kMaxN; i++) {
    f[i] = kInf;
  }
  for (LL i = 2; i * i <= n; i++) {
    for (LL j = 0; j < i - 1; j++) {
      g[j] = kInf;
    }
    for (LL j = i - 1; j < kMaxN; j++) {
      g[j] = f[j - i + 1] + i + 1;
      if (j >= i * 2 - 1) {
        g[j] = min(g[j], g[j - i * 2 + 1] + 1);
      }
    }
    for (LL j = 0; j < kMaxN; j++) {
      f[j] = min(f[j], g[j]);
    }
  }
  for (LL i = 0; i < kMaxN; i++) {
    LL x = f[i], y = (i + x) / 2;
    if (y <= n && x <= m) {
      ans += min(n - y + 1, (m - x) / 2 + 1);
    }
  }
  cout << ans - 1;
  return 0;
}
