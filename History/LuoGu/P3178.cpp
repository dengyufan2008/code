#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  LL v, f, s = 1, d, h, l;
  vector<LL> e;
} v[100001];
LL n, m, c;
pair<LL, LL> d[400001];

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
    d[p * 2].first += d[p].second * (mid - l + 1);
    d[p * 2 + 1].first += d[p].second * (r - mid);
    d[p * 2].second += d[p].second;
    d[p * 2 + 1].second += d[p].second;
    d[p].second = 0;
  }
}

void Add(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  if (l >= _l && r <= _r) {
    d[p].first += (r - l + 1) * k, d[p].second += k;
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
  d[p].first = d[p * 2].first + d[p * 2 + 1].first + d[p].second;
}

LL Ask(LL p, LL l, LL r, LL _l, LL _r) {
  if (l >= _l && r <= _r) {
    return d[p].first;
  }
  LL mid = l + r >> 1, ans = 0;
  Pushdown(p, l, r);
  if (mid >= _l) {
    ans += Ask(p * 2, l, mid, _l, _r);
  }
  if (mid < _r) {
    ans += Ask(p * 2 + 1, mid + 1, r, _l, _r);
  }
  return ans;
}

int main() {
  cin >> n >> m;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].v;
  }
  for (LL i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, 1), R(0, 1);
  for (LL i = 1; i <= n; i++) {
    Add(1, 1, n, v[i].l, v[i].l, v[i].v);
  }
  for (LL i = 1, o, x, y = 1, z; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      cin >> z;
      Add(1, 1, n, v[x].l, v[x].l, z);
    } else if (o == 2) {
      cin >> z;
      Add(1, 1, n, v[x].l, v[x].l + v[x].s - 1, z);
    } else {
      LL ans = 0;
      while (v[x].h != v[y].h) {
        if (v[v[x].h].d < v[v[y].h].d) {
          swap(x, y);
        }
        ans += Ask(1, 1, n, v[v[x].h].l, v[x].l);
        x = v[v[x].h].f;
      }
      cout << ans + Ask(1, 1, n, min(v[x].l, v[y].l), max(v[x].l, v[y].l)) << '\n';
    }
  }
  return 0;
}
