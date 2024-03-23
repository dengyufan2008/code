#include <iostream>

using namespace std;

const int kMaxN = 2001, kMaxM = 10, kMod = 1e9 + 7;
const bool Debug = 0;
int n, p[kMaxN], a[kMaxN];
namespace Sub1 {
int ans = 0;
bool b[kMaxN];

int main() {
  for (int i = 0; i <= n;) {
    ans++, b[i] ^= 1;
    i = b[i] ? p[i] : i + a[i];
  }
  cout << ans << '\n';
  return 0;
}
}  // namespace Sub1
namespace Sub2 {
int ans, f[kMaxN];

int main() {
  f[0] = ans = 1;
  for (int i = 1; i <= n; i++) {
    f[i] = 2;
    for (int j = p[i]; j < i; j++) {
      f[i] = (f[i] + f[j]) % kMod;
    }
    ans = (ans + f[i]) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
}  // namespace Sub2
namespace Sub3 {
int m, ans, l[kMaxN], f[kMaxN][1 << kMaxM], g[kMaxN][1 << kMaxM], h[kMaxN][1 << kMaxM];

int main() {
  l[0] = l[1] = -1;
  for (int i = 1; i <= n; i++) {
    if (a[i] == 2) {
      l[i + 1] = m++;
    } else if (i < n) {
      l[i + 1] = -1;
    }
  }
  fill(&f[0][0], &f[1][0], 1), fill(&h[0][0], &h[1][0], 1);
  for (int i = 1, j; i <= n; i++) {
    for (int s = 0, t; s < 1 << m; s++) {
      f[i][s] = 1;
      if (~l[i] && s >> l[i] & 1) {
        g[i][s] = 1 << l[i], h[i][s] = a[i];
      } else {
        t = s ^ (~l[i] ? 1 << l[i] : 0);
        for (j = p[i]; j < i;) {
          f[i][s] = (f[i][s] + f[j][t]) % kMod;
          int _h = h[j][t], _g = g[j][t];
          j += _h, t ^= _g;
        }
        if (j == i) {
          f[i][s] = (f[i][s] + 1) % kMod;
          t ^= ~l[i] ? 1 << l[i] : 0;
          h[i][s] = a[i];
        } else {
          h[i][s] = 1;
        }
        g[i][s] = s ^ t;
      }
    }
  }
  for (int i = 0, s = 0; i <= n;) {
    ans = (ans + f[i][s]) % kMod;
    int _h = h[i][s], _g = g[i][s];
    i += _h, s ^= _g;
  }
  cout << ans << '\n';
  return 0;
}
}  // namespace Sub3

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  int s = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    s += a[i] - 1;
  }
  p[0] = a[0] = 1;
  if (n <= 20 && !Debug) {
    return Sub1::main();
  } else if (s == 0 && !Debug) {
    return Sub2::main();
  } else {
    return Sub3::main();
  }
  return 0;
}
