#include <algorithm>
#include <cmath>
#include <iostream>
#define LL long long

using namespace std;

const int kInf = 1e9;
struct E {
  int mn = kInf, mx = -kInf;
} e[200001];
struct V {
  int l, r, d;
} v[200001];
int n, m, l, a[200001], b[200001], c[200001], ans[200001];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[i] = i;
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> v[i].l >> v[i].r;
    v[i].d = i;
  }
  l = round(pow(n, 0.5));
  sort(v + 1, v + m + 1, [](V i, V j) { return (i.l - 1) / l == (j.l - 1) / l ? i.r < j.r : i.l > j.l; });
  sort(b + 1, b + n + 1, [](int i, int j) { return a[i] < a[j]; });
  for (int i = 1; i <= n; i++) {
    c[b[i]] = c[b[i - 1]] + (a[b[i]] != a[b[i - 1]]);
  }
  for (int i = 1, x, y, num = 0, _num; i <= m; i++) {
    if (i == 1 || (v[i].l - 1) / l != (v[i - 1].l - 1) / l) {
      x = ((v[i].l - 1) / l + 1) * l, y = x - 1;
      fill(&e[0], &e[200001], (E){kInf, -kInf});
      for (; y < v[i].r;) {
        y++;
        e[c[y]].mn = min(e[c[y]].mn, y);
        e[c[y]].mx = max(e[c[y]].mx, y);
        num = max(num, e[c[y]].mx - e[c[y]].mn);
      }
      for (; y > v[i].r;) {
        y--;
        e[c[y]].mn = min(e[c[y]].mn, y);
        e[c[y]].mx = max(e[c[y]].mx, y);
        num = max(num, e[c[y]].mx - e[c[y]].mn);
      }
    }
    for (; y < v[i].r; y++, num = max(num, (e[c[y]].mx = max(e[c[y]].mx, y)) - (e[c[y]].mn = min(e[c[y]].mn, y)))) {
    }
    _num = num;
    for (; x > v[i].l; x--, num = max(num, e[c[x]].mx - x)) {
    }
    ans[v[i].d] = num, num = _num, x = ((v[i].l - 1) / l + 1) * l;
  }
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
