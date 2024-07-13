#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  LL v, f, s = 1, d, h, l;
  vector<LL> e;
} v[1000001];
LL n, m, c, ans;
string s;
pair<LL, LL> d[4000001];

void T(LL f, LL x) {
  for (LL i = 0; i < v[x].e.size(); i++) {
    if (f != v[x].e[i]) {
      v[v[x].e[i]].d = v[x].d + 1;
      T(x, v[x].e[i]);
      v[v[x].e[i]].f = x, v[x].s += v[v[x].e[i]].s;
      if (v[v[x].e[i]].s > v[v[x].e[v[x].e[0] == f]].s) {
        swap(v[x].e[v[x].e[0] == f], v[x].e[i]);
      }
    }
  }
}

void R(LL f, LL x) {
  v[x].l = ++c, v[x].h = f && v[f].e[v[f].e[0] == v[f].f] == x ? v[f].h : x;
  for (LL i : v[x].e) {
    if (f != i) {
      R(x, i);
    }
  }
}

void Pushdown(LL p, LL l, LL r) {
  LL mid = l + r >> 1;
  if (d[p].second) {
    d[p * 2].first = (d[p].second == 1) * (mid - l + 1);
    d[p * 2 + 1].first = (d[p].second == 1) * (r - mid);
    d[p * 2].second = d[p].second;
    d[p * 2 + 1].second = d[p].second;
    d[p].second = 0;
  }
}

void Change(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  Pushdown(p, l, r);
  if (l >= _l && r <= _r) {
    ans += k == 1 ? r - l + 1 - d[p].first : d[p].first;
    d[p].first = (k == 1) * (r - l + 1), d[p].second = k;
    return;
  }
  LL mid = l + r >> 1;
  if (mid >= _l) {
    Change(p * 2, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Change(p * 2 + 1, mid + 1, r, _l, _r, k);
  }
  d[p].first = d[p * 2].first + d[p * 2 + 1].first;
}

int main() {
  cin >> n;
  for (LL i = 2, x; i <= n; i++) {
    cin >> x;
    v[++x].e.push_back(i), v[i].e.push_back(x);
  }
  T(0, 1), R(0, 1);
  cin >> m;
  for (LL i = 1, x; i <= m; i++, ans = 0) {
    cin >> s >> x;
    x++;
    if (s[0] == 'i') {
      while (v[x].h != v[1].h) {
        Change(1, 1, n, v[v[x].h].l, v[x].l, 1);
        x = v[v[x].h].f;
      }
      Change(1, 1, n, min(v[x].l, v[1].l), max(v[x].l, v[1].l), 1);
    } else {
      Change(1, 1, n, v[x].l, v[x].l + v[x].s - 1, -1);
    }
    cout << ans << '\n';
  }
  return 0;
}
