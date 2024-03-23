#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <unordered_map>
#define LL long long

using namespace std;

ifstream cin("canteen.in");
ofstream cout("canteen.out");

const LL kMaxN = 2e5 + 1;
struct A {
  LL l, m, r;
};
struct E {
  LL x1, y1, x2, y2;
} e[kMaxN];
struct L {
  LL x, l, r;
} l[kMaxN * 3];
struct V {
  LL x, y, w, t, k, l, r;
} v[kMaxN];
LL n, m, w, _l, _v, _w, s, o[kMaxN];
unordered_map<LL, LL> f, d;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

LL GetRoot(LL x) {
  if (f.find(x) == f.end()) {
    f[x] = x, d[x] = kMaxN;
  }
  return f[x] == x ? x : f[x] = GetRoot(f[x]);
}

void Pushdown(LL p) {
  if (v[p].t) {
    v[v[p].l].w += v[p].t, v[v[p].l].t += v[p].t;
    v[v[p].r].w += v[p].t, v[v[p].r].t += v[p].t;
    v[p].t = 0;
  }
}

A Split(LL p, LL x) {
  if (!p) {
    return {};
  }
  Pushdown(p);
  if (v[p].y < x) {
    A q = Split(v[p].r, x);
    v[p].r = q.l;
    return {p, q.m, q.r};
  } else if (v[p].x > x) {
    A q = Split(v[p].l, x);
    v[p].l = q.r;
    return {q.l, q.m, p};
  } else {
    LL l = v[p].l, r = v[p].r;
    v[p].l = v[p].r = 0;
    return {l, p, r};
  }
}

LL Merge(LL p, LL q) {
  if (!p || !q) {
    return p | q;
  }
  Pushdown(p), Pushdown(q);
  if (v[p].k < v[q].k) {
    v[p].r = Merge(v[p].r, q);
    return p;
  } else {
    v[q].l = Merge(p, v[q].l);
    return q;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> w;
  for (LL i = 1; i <= n; i++) {
    cin >> e[i].x1 >> e[i].y1 >> e[i].x2 >> e[i].y2;
  }
  for (LL i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    l[++_l] = {x, y, -i};
  }
  sort(e + 1, e + n + 1, [](E i, E j) {
    return i.x1 == i.x2 && j.x1 != j.x2 ||
           i.x1 == i.x2 && j.x1 == j.x2 && (i.x1 < j.x1 || i.x1 == j.x1 && i.y1 < j.y1) ||
           i.x1 != i.x2 && j.x1 != j.x2 && (i.y1 < j.y1 || i.y1 == j.y1 && i.x1 > j.x1);
  });
  for (LL i = 1, j = 1; i <= n && e[i].x1 == e[i].x2; i = j) {
    if (e[i].y1 != e[i].y2) {
      LL y1 = e[i].y1, y2 = e[i].y2;
      for (; j <= n && e[j].x1 == e[j].x2 && e[i].x1 == e[j].x1; j++) {
        if (e[j].y1 != e[j].y2) {
          if (e[j].y1 <= y2) {
            y2 = max(y2, e[j].y2);
          } else {
            l[++_l] = {e[i].x1, y1, y2};
            y1 = e[j].y1, y2 = e[j].y2;
          }
        }
      }
      l[++_l] = {e[i].x1, y1, y2};
    } else {
      j++;
    }
  }
  for (LL i = n, j = n; i >= 1 && e[i].y1 == e[i].y2; i = j) {
    if (e[i].x1 != e[i].x2) {
      LL x1 = e[i].x1, x2 = e[i].x2;
      for (; j >= 1 && e[j].y1 == e[j].y2 && e[i].y1 == e[j].y1; j--) {
        if (e[j].x1 != e[j].x2) {
          if (e[j].x1 <= x2) {
            x2 = max(x2, e[j].x2);
          } else {
            l[++_l] = {x1, e[i].y1, -1145140}, l[++_l] = {x2 + 1, e[i].y1, -1919810};
            x1 = e[j].x1, x2 = e[j].x2;
          }
        }
      }
      l[++_l] = {x1, e[i].y1, -1145140}, l[++_l] = {x2 + 1, e[i].y1, -1919810};
    } else {
      j--;
    }
  }
  sort(l + 1, l + _l + 1, [](L i, L j) { return i.x < j.x || i.x == j.x && i.r < j.r; });
  s = _v = _w = 1, v[1] = {0, w, 1, 0, (LL)(Rand() / 2)};
  for (LL i = 1, j = 1; i <= _l; i = j) {
    for (; j <= _l && l[i].x == l[j].x; j++) {
      if (l[j].l <= l[j].r) {
        A p = Split(s, l[j].l - 1), q = Split(p.r, l[j].r);
        v[q.l].w += kMaxN, v[q.l].t += kMaxN, _w += kMaxN;
        p.r = Merge(q.l, Merge(q.m, q.r)), s = Merge(p.l, Merge(p.m, p.r));
      } else if (l[j].r == -1145140) {
        A p = Split(s, l[j].l);
        v[++_v] = {l[j].l, v[p.m].y, ++_w, 0, (LL)(Rand() / 2)};
        v[p.m].y = l[j].l - 1;
        f[_w] = GetRoot(v[p.m].w), d[_w] = kMaxN;
        p.m = Merge(p.m, _v);
        s = Merge(p.l, Merge(p.m, p.r));
      } else if (l[j].r == -1919810) {
        A p = Split(s, l[j].l - 1), q = Split(p.r, l[j].l);
        if (GetRoot(v[p.m].w) != GetRoot(v[q.m].w)) {
          d[GetRoot(v[q.m].w)] = min(d[GetRoot(v[q.m].w)], d[GetRoot(v[p.m].w)]);
          f[GetRoot(v[p.m].w)] = GetRoot(v[q.m].w);
        }
        v[p.m].y = v[q.m].y, v[q.m] = {}, q.m = 0;
        p.r = Merge(q.l, Merge(q.m, q.r));
        s = Merge(p.l, Merge(p.m, p.r));
      } else {
        A p = Split(s, l[j].l);
        o[-l[j].r] = GetRoot(v[p.m].w);
        d[GetRoot(v[p.m].w)] = min(d[GetRoot(v[p.m].w)], -l[j].r);
        s = Merge(p.l, Merge(p.m, p.r));
      }
    }
  }
  for (LL i = 1; i <= m; i++) {
    cout << d[GetRoot(o[i])] << '\n';
  }
  return 0;
}
