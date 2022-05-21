#include <algorithm>
#include <cmath>
#include <iostream>
#define LL long long

using namespace std;

struct E {
  LL x, p, n;
} e[133334];
struct V {
  LL l, r, t, d;
} v[133334];
LL n, m, l, _e, _v, a[133334], c[1000001], ans[133334];
char ch;

int main() {
  cin >> n >> m;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (LL i = 1, x, y; i <= m; i++) {
    cin >> ch >> x >> y;
    if (ch == 'Q') {
      v[++_v] = {x, y, _e, _v};
    } else {
      e[++_e] = {x, a[x], a[x] = y};
    }
  }
  l = round(pow(n, 2.0 / 3.0));
  sort(v + 1, v + _v + 1, [](V i, V j) { return (i.l - 1) / l == (j.l - 1) / l && (i.r - 1) / l == (j.r - 1) / l ? i.t < j.t : i.l < j.l || i.l == j.l && i.r < j.r; });
  for (LL i = 1, x = v[1].l, y = v[1].l - 1, t = _e; i <= _v; i++) {
    ans[v[i].d] = ans[v[i - 1].d];
    for (; x < v[i].l; ans[v[i].d] -= !--c[a[x++]]) {
    }
    for (; x > v[i].l; ans[v[i].d] += !c[a[--x]]++) {
    }
    for (; y < v[i].r; ans[v[i].d] += !c[a[++y]]++) {
    }
    for (; y > v[i].r; ans[v[i].d] -= !--c[a[y--]]) {
    }
    for (; t < v[i].t;) {
      t++;
      a[e[t].x] = e[t].n;
      if (e[t].x >= x && e[t].x <= y) {
        ans[v[i].d] += !c[e[t].n]++ - !--c[e[t].p];
      }
    }
    for (; t > v[i].t;) {
      a[e[t].x] = e[t].p;
      if (e[t].x >= x && e[t].x <= y) {
        ans[v[i].d] += !c[e[t].p]++ - !--c[e[t].n];
      }
      t--;
    }
  }
  for (LL i = 1; i <= _v; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
