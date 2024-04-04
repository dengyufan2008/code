#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 2, kInf = 1e9, kMod = 1e9 + 7;
struct A {
  int w, l, r;
} a[kMaxN];
struct V {
  int o, ot, w, wd, wt, c, cd, l, r;
  unsigned LL u;
} v[kMaxN];
int n, m, w, u, t, s, c[kMaxN];
mt19937_64 Rand(chrono::steady_clock().now().time_since_epoch().count());

void Tag(int p, int x) {
  v[p].w += x, v[p].wd += x, v[p].wt += x;
}

void Move(int p, int x) {
  v[p].o += x, v[p].ot += x;
}

void Pushdown(int p) {
  if (v[p].wt) {
    Tag(v[p].l, v[p].wt), Tag(v[p].r, v[p].wt);
    v[p].wt = 0;
  }
  if (v[p].ot) {
    Move(v[p].l, v[p].ot), Move(v[p].r, v[p].ot);
    v[p].ot = 0;
  }
}

void Update(int p) {
  v[p].wd = v[p].w, v[p].cd = v[p].c;
  for (int i : {v[p].l, v[p].r}) {
    if (v[i].wd > v[p].wd) {
      v[p].wd = v[i].wd, v[p].cd = v[i].cd;
    } else if (v[i].wd == v[p].wd) {
      v[p].cd = (v[p].cd + v[i].cd) % kMod;
    }
  }
}

pair<int, int> Split(int &p, int x) {
  if (!p) {
    return {0, 0};
  }
  Pushdown(p);
  if (v[p].o <= x) {
    auto q = Split(v[p].r, x);
    v[p].r = q.first, Update(p);
    return {p, q.second};
  } else {
    auto q = Split(v[p].l, x);
    v[p].l = q.second, Update(p);
    return {q.first, p};
  }
}

int Merge(int p, int q) {
  if (!p || !q) {
    return p | q;
  }
  Pushdown(p), Pushdown(q);
  if (v[p].u < v[q].u) {
    v[p].r = Merge(v[p].r, q);
    return Update(p), p;
  } else {
    v[q].l = Merge(p, v[q].l);
    return Update(q), q;
  }
}

void Update(int p, int q, int o) {
  if (v[p].w < v[q].wd + o) {
    v[p].w = v[p].wd = v[q].wd + o;
    v[p].c = v[p].cd = v[q].cd;
  } else if (v[p].w == v[q].wd + o) {
    v[p].c = v[p].cd = (v[p].c + v[q].cd) % kMod;
  }
}

void Print() {
  auto p = Split(s, m);
  auto q = Split(p.first, m - 1);
  if (u) {
    cout << v[q.second].wd << ' ' << v[q.second].cd << '\n';
  } else {
    cout << v[q.second].wd << '\n';
  }
  p.first = Merge(q.first, q.second);
  s = Merge(p.first, p.second);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> w >> u;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].w >> a[i].l >> a[i].r;
    c[a[i].l]++, c[a[i].r + 1]--;
  }
  for (int i = 1; i <= m; i++) {
    c[i] += c[i - 1];
  }
  for (int i = 1; i <= m; i++) {
    c[i] = c[i - 1] + !c[i];
  }
  m -= c[m];
  for (int i = 1; i <= n; i++) {
    a[i].l -= c[a[i].l], a[i].r -= c[a[i].r];
  }
  sort(a + 1, a + n + 1, [](A i, A j) {
    return i.l < j.l || i.l == j.l && i.r < j.r;
  });
  v[0].w = v[0].wd = -kInf, s = t = 1;
  v[1].c = v[1].cd = 1, v[1].u = Rand();
  for (int i = 1; i <= n; i++) {
    v[++t].o = a[i].r, v[t].u = Rand();
    auto p = Split(s, a[i].r);
    auto q = Split(p.first, a[i].l - 2);
    Update(t, q.second, 0);
    if (a[i].w <= w) {
      auto r = Split(q.second, a[i].r + a[i].w - w - 1);
      Update(t, r.second, 1);
      Tag(r.first, 1), Move(r.first, w - a[i].w);
      s = Merge(r.first, t);
    } else {
      s = t;
    }
  }
  Print();
  return 0;
}
