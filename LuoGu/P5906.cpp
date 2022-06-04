#include <algorithm>
#include <cmath>
#include <iostream>
#define LL long long

using namespace std;

const int kInf = 1e9;
struct E {
  int mx = -kInf, mn = kInf, _mx = -kInf, _mn = kInf;
} e[200001];
struct V {
  int l, r, d;
} v[200001];
int n, m, k, a[200001], b[200001], l[200001], ans[200001];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
    l[i] = i;
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> v[i].l >> v[i].r;
    v[i].d = i;
  }
  k = round(pow(n, 0.5));
  sort(v + 1, v + m + 1, [](V i, V j) { return (i.l - 1) / k == (j.l - 1) / k ? i.r < j.r : i.l < j.l; });
  sort(l + 1, l + n + 1, [](int i, int j) { return b[i] < b[j]; });
  for (int i = 1; i <= n; i++) {
    a[l[i]] = a[l[i - 1]] + (b[l[i]] != b[l[i - 1]]);
  }
  for (int i = 1, x, _x, y, num = 0, _num; i <= m; i++) {
    if (i == 1 || (v[i].l - 1) / k != (v[i - 1].l - 1) / k) {
      y = min(((v[i].l - 1) / k + 1) * k - 1, v[i].r), x = _x = y + 1, num = 0;
      fill(e + 1, e + 200001, e[0]);
    }
    for (; y < v[i].r;) {
      y++;
      e[a[y]].mn = min(e[a[y]].mn, y);
      e[a[y]].mx = max(e[a[y]].mx, y);
      num = max(num, e[a[y]].mx - e[a[y]].mn);
    }
    _num = num;
    for (; x > v[i].l;) {
      x--;
      e[a[x]]._mn = min(min(e[a[x]].mn, e[a[x]]._mn), x);
      e[a[x]]._mx = max(max(e[a[x]].mx, e[a[x]]._mx), x);
      num = max(num, e[a[x]]._mx - e[a[x]]._mn);
    }
    ans[v[i].d] = num, num = _num, x = _x;
  }
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
