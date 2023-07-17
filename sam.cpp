#include <iostream>
#define LL long long

using namespace std;

const LL kMaxN = 1e6 + 1;
struct V {
  LL l, c, f, e[26];
  bool b;
} v[kMaxN << 1];
LL n, m, r, ans, c[kMaxN << 1], d[kMaxN << 1];
string s;

int main() {
  cin >> s;
  n = s.size(), v[0].f = -1;
  for (LL i = 0, j, p; i < n; i++) {
    p = s[i] - 'a', v[++m].l = v[r].l + 1;
    for (j = r; ~j && !v[j].e[p]; j = v[j].f) {
      v[j].e[p] = m;
    }
    if (~j) {
      LL q = v[j].e[p];
      if (v[q].l == v[j].l + 1) {
        v[m].f = q, r = m;
      } else {
        v[++m] = v[q], v[m].l = v[j].l + 1;
        for (; ~j && v[j].e[p] == q; j = v[j].f) {
          v[j].e[p] = m;
        }
        r = m - 1, v[q].f = v[m - 1].f = m, v[m].b = 1;
      }
    } else {
      r = m;
    }
  }
  for (LL i = 1; i <= m; i++) {
    c[v[i].l]++;
  }
  for (LL i = 1; i <= m; i++) {
    c[i] += c[i - 1];
  }
  for (LL i = 1; i <= m; i++) {
    d[c[v[i].l]--] = i;
  }
  for (LL i = m; i >= 1; i--) {
    v[d[i]].c += !v[d[i]].b, v[v[d[i]].f].c += v[d[i]].c;
  }
  for (LL i = 1; i <= m; i++) {
    if (v[i].c > 1) {
      ans = max(ans, v[i].c * v[i].l);
    }
  }
  cout << ans;
  return 0;
}
