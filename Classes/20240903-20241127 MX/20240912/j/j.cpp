#include <bitset>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

int t, a[256];
LL n;

LL Pow(LL x, int y, int mod) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % mod;
    }
    x = x * x % mod;
  }
  return ans;
}

LL Calc1() {
  LL ans = 0;
  for (int i = 0; i < 256; i++) {
    ans = (ans + 1LL * i * a[i]) % 255;
  }
  if (n >= 8) {
    ans = Pow(ans, 128, 255);
  } else {
    for (int i = 2; i <= n; i++) {
      ans = Pow(ans, i, 255);
    }
  }
  return ans;
}

LL Calc20() {
  int d[11] = {};
  for (int i = 0, t = 0; i < 256; i++) {
    for (int j = 1; j <= a[i]; j++) {
      d[t++] = i;
    }
  }
  int t = 1;
  for (int s = 0; s < 1 << n; s++) {
    if (__builtin_popcount(s) == n >> 1) {
      int w = 0;
      for (int i = 0; i < n; i++) {
        if (s >> i & 1) {
          w = (w - d[i] + 257) % 257;
        } else {
          w = (w + d[i]) % 257;
        }
      }
      t = t * w % 257;
    }
  }
  for (int i = 2; i <= n >> 1; i++) {
    t = Pow(t, i * i, 257);
  }
  return n & 1 ? Pow(t, n + 1 >> 1, 257) : t;
}

LL Calc21() {
  int mx = 0, s = 0;
  LL m = n >> 1;
  bitset<257> f[512], g[512];
  for (int i = 1; i < 256; i++) {
    s = (s + 1LL * a[i] * i) % 257;
    if (a[i] > a[mx]) {
      mx = i;
    }
  }
  s = s * 129 % 257, f[0][0] = g[0][0] = 1;
  for (int i = 0; i < 256; i++) {
    if (i != mx) {
      for (int j = 0; j <= a[i]; j++) {
        for (int k = 0; j + k <= n - a[mx]; k++) {
          int w = i * j % 257;
          g[j + k] |= f[k] << w | f[k] >> 257 - w;
        }
      }
      for (int j = 0; j <= n - a[mx]; j++) {
        f[j] = g[j];
      }
    }
  }
  for (int i = max(m - n + a[mx], 0LL); i <= a[mx] && i <= m; i++) {
    if (f[m - i][(s - 1LL * i * mx % 257 + 257) % 257]) {
      return 0;
    }
  }
  return 1;
}

LL Calc2() {
  int mx = 0;
  for (int i = 0; i < 256; i++) {
    mx = max(mx, a[i]);
  }
  if (n >= 512 && n - mx >= 256) {
    return 0;
  } else if (n <= 11) {
    return Calc20();
  } else {
    return Calc21();
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    n = 0;
    for (int i = 0; i < 256; i++) {
      a[i] = 0;
    }
    int m;
    cin >> m;
    for (int i = 1, x; i <= m; i++) {
      cin >> x >> a[x], n += a[x];
    }
    cout << (Calc1() * 32896 + Calc2() * 32640) % 65535 << '\n';  // CRT
  }
  return 0;
}
