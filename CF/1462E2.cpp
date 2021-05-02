#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMod = 1e9 + 7;

LL t, n, m, k, ans, a[200010], b[200010], c[200010], f[200010];

LL Pow(LL x, LL y) {
  LL ret = 1;
  while (y) {
    if (y & 1LL) {
      ret = ret * x % kMod;
    }
    x = x * x % kMod, y >>= 1;
  }
  return ret;
}

LL C(LL n, LL m) {
  return m > n || m < 0 ? 0 : f[n] * c[m] % kMod * c[n - m] % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  c[0] = f[0] = 1;
  for (int i = 1; i <= 200000; i++) {
    f[i] = f[i - 1] * i % kMod;
  }
  for (int i = 1; i <= 200000; i++) {
    c[i] = Pow(f[i], kMod - 2);  //预处理组合数
  }
  cin >> t;
  while (t--) {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      b[a[i]]++;
    }
    ans = 0;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
      b[i] += b[i - 1];
    }
    for (int i = n; i >= 1; i--) {
      if (a[i] > k) {
        ans = (ans + C(i - b[a[i] - k - 1] - 1, m - 1)) % kMod;
      } else {
        ans = (ans + C(i - 1, m - 1)) % kMod;
      }
    }
    cout << ans << '\n';
    fill(&b[1], &b[n] + 1, 0);
  }
  return 0;
}
