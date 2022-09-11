#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL a, b, l;
} v[10001];
LL n, m, ans;

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].a >> v[i].b;
    for (LL j = v[i].a; j; j /= 10, v[i].l++) {
    }
    v[i].l = max(v[i].l, 1LL);
  }
  cin >> m;
  for (LL i = 1; i <= n; i++) {
    LL s = 10, t = 1;
    for (LL j = 1; j <= v[i].l; j <<= 1) {
      if (j & v[i].l) {
        t = t * s % m;
      }
      s = s * s % m;
    }
    for (LL j = 1; j <= v[i].b; j <<= 1) {
      if (j & v[i].b) {
        ans = (ans * t % m + v[i].a) % m;
      }
      v[i].a = (v[i].a * t % m + v[i].a) % m;
      t = t * t % m;
    }
  }
  cout << ans << '\n';
  return 0;
}
