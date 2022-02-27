#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  LL v, f, s = 1, d, h, l;
  vector<LL> e;
} v[30001];
struct D {
  int m, s, t;
} d[120001];
LL n, m, c;
string s;

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
  if (d[p].t) {
    d[p * 2].s += d[p].t * (mid - l + 1);
    d[p * 2 + 1].s += d[p].t * (r - mid);
    d[p * 2].m += d[p].t;
    d[p * 2 + 1].m += d[p].t;
    d[p * 2].t += d[p].t;
    d[p * 2 + 1].t += d[p].t;
    d[p].t = 0;
  }
}

void Add(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  if (l >= _l && r <= _r) {
    d[p].s += (r - l + 1) * k, d[p].m += k, d[p].t += k;
    return;
  }
  LL mid = l + r >> 1;
  Pushdown(p, l, r);
  if (mid >= _l) {
    Add(p * 2, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Add(p * 2 + 1, mid + 1, r, _l, _r, k);
  }
  d[p].s = d[p * 2].s + d[p * 2 + 1].s, d[p].m = max(d[p * 2].m, d[p * 2 + 1].m);
}

LL Ask(LL p, LL l, LL r, LL _l, LL _r, bool b) {
  if (l >= _l && r <= _r) {
    return b ? d[p].s : d[p].m;
  }
  LL mid = l + r >> 1, ans = 0;
  Pushdown(p, l, r);
  if (mid >= _l) {
    LL t = Ask(p * 2, l, mid, _l, _r, b);
    ans = b ? ans + t : max(ans, t);
  }
  if (mid < _r) {
    LL t = Ask(p * 2 + 1, mid + 1, r, _l, _r, b);
    ans = b ? ans + t : max(ans, t);
  }
  return ans;
}

int main() {
  cin >> n;
  for (LL i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].v;
  }
  T(0, 1), R(0, 1);
  for (LL i = 1; i <= n; i++) {
    Add(1, 1, n, v[i].l, v[i].l, v[i].v);
  }
  cin >> m;
  for (LL i = 1, x, y; i <= m; i++) {
    cin >> s >> x >> y;
    if (s == "CHANGE") {
      Add(1, 1, n, v[x].l, v[x].l, y - v[x].v);
    } else {
      LL ans = 0;
      while (v[x].h != v[y].h) {
        if (v[v[x].h].d < v[v[y].h].d) {
          swap(x, y);
        }
        LL t = Ask(1, 1, n, v[v[x].h].l, v[x].l, s == "QSUM");
        ans = s == "QSUM" ? ans + t : max(ans, t);
        x = v[v[x].h].f;
      }
      LL t = Ask(1, 1, n, min(v[x].l, v[y].l), max(v[x].l, v[y].l), s == "QSUM");
      cout << (s == "QSUM" ? ans + t : max(ans, t)) << '\n';
    }
  }
  return 0;
}
