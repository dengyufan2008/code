#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  LL v, f, s = 1, d, h, l;
  vector<LL> e;
} v[100001];
LL n, m, s, c, mod;
pair<LL, LL> d[400001];

void T(LL f, LL x) {
  for (LL i = 0; i < v[x].e.size(); i++) {
    if (f != v[x].e[i]) {
      v[v[x].e[i]].d = v[x].d + 1;
      T(x, v[x].e[i]);
      v[v[x].e[i]].f = x, v[x].s += v[v[x].e[i]].s;
      if (v[x].e[0] == f || v[v[x].e[i]].s > v[v[x].e[0]].s) {
        swap(v[x].e[0], v[x].e[i]);
      }
    }
  }
}

void R(LL f, LL x) {
  v[x].l = ++c, v[x].h = f && v[f].e[0] == x ? v[f].h : x;
  for (LL i : v[x].e) {
    if (f != i) {
      R(x, i);
    }
  }
}

void Pushdown(LL p, LL l, LL r) {
  LL mid = l + r >> 1;
  if (d[p].second) {
    d[p * 2].first = (d[p * 2].first + d[p].second * (mid - l + 1)) % mod;
    d[p * 2 + 1].first = (d[p * 2 + 1].first + d[p].second * (r - mid)) % mod;
    d[p * 2].second = (d[p * 2].second + d[p].second) % mod;
    d[p * 2 + 1].second = (d[p * 2 + 1].second + d[p].second) % mod;
    d[p].second = 0;
  }
}

void Add(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  if (l >= _l && r <= _r) {
    d[p].first = (d[p].first + (r - l + 1) * k) % mod, d[p].second = (d[p].second + k) % mod;
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
  d[p].first = (d[p * 2].first + d[p * 2 + 1].first) % mod;
}

LL Ask(LL p, LL l, LL r, LL _l, LL _r) {
  if (l >= _l && r <= _r) {
    return d[p].first;
  }
  LL mid = l + r >> 1, ans = 0;
  Pushdown(p, l, r);
  if (mid >= _l) {
    ans = (ans + Ask(p * 2, l, mid, _l, _r)) % mod;
  }
  if (mid < _r) {
    ans = (ans + Ask(p * 2 + 1, mid + 1, r, _l, _r)) % mod;
  }
  return ans;
}

int main() {
  cin >> n >> m >> s >> mod;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].v;
    v[i].v %= mod;
  }
  for (LL i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, s), R(0, s);
  for (LL i = 1; i <= n; i++) {
    Add(1, 1, n, v[i].l, v[i].l, v[i].v);
  }
  for (LL i = 1, o, x, y, z; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      cin >> y >> z;
      while (v[x].h != v[y].h) {
        if (v[v[x].h].d < v[v[y].h].d) {
          swap(x, y);
        }
        Add(1, 1, n, v[v[x].h].l, v[x].l, z);
        x = v[v[x].h].f;
      }
      Add(1, 1, n, min(v[x].l, v[y].l), max(v[x].l, v[y].l), z);
    } else if (o == 2) {
      cin >> y;
      LL ans = 0;
      while (v[x].h != v[y].h) {
        if (v[v[x].h].d < v[v[y].h].d) {
          swap(x, y);
        }
        ans = (ans + Ask(1, 1, n, v[v[x].h].l, v[x].l)) % mod;
        x = v[v[x].h].f;
      }
      cout << (ans + Ask(1, 1, n, min(v[x].l, v[y].l), max(v[x].l, v[y].l))) % mod << '\n';
    } else if (o == 3) {
      cin >> z;
      Add(1, 1, n, v[x].l, v[x].l + v[x].s - 1, z);
    } else {
      cout << Ask(1, 1, n, v[x].l, v[x].l + v[x].s - 1) << '\n';
    }
  }
  return 0;
}
