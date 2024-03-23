#include <iostream>
#define LL long long

using namespace std;

const LL kMaxN = 1e6 + 1;
struct V {
  LL f, l, e[26];
} v[kMaxN << 1];
LL n, m = 1, ans;
string s;

LL Add(LL r, LL i) {
  if (v[r].e[i]) {
    LL c = v[r].e[i], p = r;
    if (v[p].l + 1 == v[c].l) {
      return c;
    } else {
      v[++m] = v[c], v[m].l = v[p].l + 1;
      for (; p && v[p].e[i] == c; p = v[p].f) {
        v[p].e[i] = m;
      }
      v[c].f = m;
      return m;
    }
  } else {
    LL c = ++m, p = r;
    v[c].l = v[p].l + 1;
    for (; p && !v[p].e[i]; p = v[p].f) {
      v[p].e[i] = c;
    }
    if (p) {
      LL q = v[p].e[i];
      if (v[p].l + 1 == v[q].l) {
        v[c].f = q;
      } else {
        v[++m] = v[q], v[m].l = v[p].l + 1;
        for (; p && v[p].e[i] == q; p = v[p].f) {
          v[p].e[i] = m;
        }
        v[q].f = v[c].f = m;
      }
    } else {
      v[c].f = 1;
    }
    return c;
  }
}

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> s;
    for (LL j = 0, r = 1; j < s.size(); j++) {
      r = Add(r, s[j] - 'a');
    }
  }
  for (LL i = 1; i <= m; i++) {
    ans += v[i].l - v[v[i].f].l;
  }
  cout << ans << '\n'
       << m << '\n';
  return 0;
}
