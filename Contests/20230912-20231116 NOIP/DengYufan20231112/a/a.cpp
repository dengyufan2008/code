#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const LL kMaxN = 3e5 + 1;
struct A {
  LL c, w, v;
} a[kMaxN];
LL t, n, k, s, c, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].c >> a[i].w >> a[i].v;
    }
    sort(a + 1, a + n + 1, [](A i, A j) { return i.v > j.v || i.v == j.v && i.w > j.w; });
    c = ans = 0;
    for (int i = 1, j; i <= n; i = j) {
      for (; i <= n; i++) {
        if (a[i].w & 1) {
          LL t = min(c, a[i].c);
          c -= t, a[i].c -= t;
        }
        if (a[i].c) {
          break;
        }
      }
      s = 0, ans += a[i].v;
      for (j = i; j <= n && s <= k; j++) {
        if (a[j].w & 1) {
          LL t = min(c, a[j].c);
          c -= t, a[j].c -= t;
        }
        s += a[j].w * a[j].c;
      }
      if (s > k) {
        j--, s -= a[j].w * a[j].c, a[j].c -= (k - s) / a[j].w;
        if (!(a[j].w & 1) && ((k - s) & 1)) {
          c++;
        }
        LL w = k / a[j].w, t = a[j].c / w;
        ans += t * a[j].v, a[j].c %= w;
        while (j <= n && !a[j].c) {
          j++;
        }
      } else {
        break;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
