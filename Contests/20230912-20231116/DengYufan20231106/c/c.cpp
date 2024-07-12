#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 3e5 + 2, kMaxM = 1 << 20, kMod = 1e9 + 7;
int n, m, l, a[kMaxN];
LL ans, f[kMaxN], g[kMaxN], c[kMaxM];

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  l = m >> 1;

  f[0] = 1, fill(&c[0], &c[1 << l], 1);
  for (int i = 1; i <= n; i++) {
    int s = a[i] >> l << l, t = a[i] & ~(-1 << l);
    f[i] = c[t];
    for (int j = s; j; j = (j - 1) & s) {
      f[i] = (f[i] + c[j | t]) % kMod;
    }
    for (int j = t; j < 1 << l; j = (j + 1) | t) {
      c[j | s] = (c[j | s] + f[i]) % kMod;
    }
  }
  fill(&c[0], &c[1 << m], 0);

  g[n + 1] = 1, fill(&c[0], &c[1 << l], 1);
  for (int i = n; i >= 1; i--) {
    int s = a[i] >> l << l, t = a[i] & ~(-1 << l);
    g[i] = c[t];
    for (int j = s; j; j = (j - 1) & s) {
      g[i] = (g[i] + c[j | t]) % kMod;
    }
    for (int j = t; j < 1 << l; j = (j + 1) | t) {
      c[j | s] = (c[j | s] + g[i]) % kMod;
    }
  }
  fill(&c[0], &c[1 << m], 0);

  for (int i = 1; i <= n; i++) {
    f[i] = (f[i] - c[a[i]] + kMod) % kMod;
    c[a[i]] = (c[a[i]] + c[a[i]] + f[i]) % kMod;
    ans = (ans + f[i] * g[i]) % kMod;
  }
  cout << ans;
  return 0;
}
