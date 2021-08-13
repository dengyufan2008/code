#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct A {
  LL d, l, c;
};
struct V {
  bool b;
  LL l = 0x7fffffff, c = 1919810;
  vector<A> e;
} v[501];
LL n, m, x;

int main() {
  freopen("mroute.in", "r", stdin);
  freopen("mroute.out", "w", stdout);
  cin >> n >> m >> x;
  for (LL i = 1, p, q, l, c; i <= m; i++) {
    cin >> p >> q >> l >> c;
    v[p].e.push_back({q, l, c});
    v[q].e.push_back({p, l, c});
  }
  v[1].l = 0;
  for (LL i = 2; i <= n; i++) {
    LL mn = 0;
    for (LL j = 1; j <= n; j++) {
      if (!v[j].b && v[mn].l + x / v[mn].c > v[j].l + x / v[j].c) {
        mn = j;
      }
    }
    v[mn].b = 1;
    for (A j : v[mn].e) {
      if (v[j.d].l + x / v[j.d].c > v[mn].l + j.l + x / min(v[mn].c, j.c)) {
        v[j.d].l = v[mn].l + j.l;
        v[j.d].c = min(v[mn].c, j.c);
      }
    }
  }
  cout << v[n].l + x / v[n].c << endl;
  return 0;
}
