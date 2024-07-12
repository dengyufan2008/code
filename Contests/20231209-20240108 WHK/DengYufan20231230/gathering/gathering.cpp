#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

ifstream cin("gathering.in");
ofstream cout("gathering.out");

const int kMaxN = 5e5 + 1, kMaxM = 1e5 + 1, kMaxL = 801;
struct V {
  int s, p, et;
} v[kMaxN];
struct D {
  int p, w, t, mn, mx, l, r;
} d[kMaxN << 5];
struct T {
  int x, y, w;
} t[kMaxN << 5];
struct Q {
  int l, r, d;
} q[kMaxM];
int n, m, b, _d, _t, e[kMaxN], a[kMaxN], s[kMaxL], ans[kMaxM];

void Pushdown(int p) {
  int l = d[p].l, r = d[p].r, o = l ? l : r;
  d[l].w += d[p].t, d[l].t += d[p].t;
  d[r].w += d[p].t, d[r].t += d[p].t;
  d[o].p = d[p].p, d[o].w = d[p].w;
  d[p].t = 0;
}

void Pushup(int p) {
  int l = d[p].l, r = d[p].r, o = l ? l : r;
  d[p].mn = min(d[l].mn, d[r].mn);
  d[p].mx = max(d[l].mx, d[r].mx);
  d[p].p = d[o].p, d[p].w = d[o].w;
  if (l && r && d[l].mx && d[l].mx != d[r].p) {
    d[r].w ? t[++_t] = {d[r].p, d[r].mn, d[r].w}, 0 : 0;
    d[r].p = d[l].mx, d[r].w = 0;
  }
}

void Merge(int &p, int &q, int l, int r) {
  if (!p || !q) {
    p |= q;
    return;
  }
  Pushdown(p), Pushdown(q);
  int mid = l + r >> 1;
  Merge(d[p].l, d[q].l, l, mid);
  Merge(d[p].r, d[q].r, mid + 1, r);
  Pushup(p);
}

void Add(int &p, int l, int r, int x) {
  p = ++_d;
  if (l == r) {
    d[p].mn = d[p].mx = x;
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= x) {
    Add(d[p].l, l, mid, x);
  } else {
    Add(d[p].r, mid + 1, r, x);
  }
  Pushup(p);
}

void Calc(int p, int l, int r) {
  if (!d[p].mx) {
    return;
  }
  d[p].w ? t[++_t] = {d[p].p, d[p].mn, d[p].w}, 0 : 0;
  d[p].w = 0, Pushdown(p);
  int mid = l + r >> 1;
  Calc(d[p].l, l, mid), Calc(d[p].r, mid + 1, r);
}

void S(int x) {
  int mx = 0;
  for (int i = v[x].et; i; i = e[i]) {
    S(i), v[x].s += v[i].s;
    if (!mx || v[mx].s < v[i].s) {
      mx = i;
    }
  }
  v[x].s++, !mx && (mx = x), v[x].p = v[mx].p, Add(v[mx].p, 1, n, x);
  for (int i = v[x].et; i; i = e[i]) {
    Calc(v[i].p, 1, n), Merge(v[x].p, v[i].p, 1, n);
  }
  d[v[x].p].w++, d[v[x].p].t++;
}

int Block(int x) { return (x - 1) / b; }
int Left(int x) { return (x - 1) / b * b + 1; }
int Right(int x) { return (x - 1) / b * b + b; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    e[i] = v[x].et, v[x].et = i;
  }
  d[0].mn = n + 1, S(v[0].et), Calc(v[v[0].et].p, 1, n);
  sort(t + 1, t + _t + 1, [](T i, T j) { return i.x < j.x; });
  for (int i = 1; i <= m; i++) {
    cin >> q[i].l >> q[i].r;
    q[i].d = i;
  }
  sort(q + 1, q + m + 1, [](Q i, Q j) { return i.l < j.l; });
  b = sqrt(n);
  for (int i = 1, j = 1; i <= m; i++) {
    for (; j <= _t && t[j].x < q[i].l; j++) {
      a[t[j].y] += t[j].w, s[Block(t[j].y)] += t[j].w;
    }
    if (Block(q[i].l) == Block(q[i].r)) {
      for (int k = q[i].l; k <= q[i].r; k++) {
        ans[q[i].d] += a[k];
      }
    } else {
      for (int k = q[i].l; k <= Right(q[i].l); k++) {
        ans[q[i].d] += a[k];
      }
      for (int k = Block(q[i].l) + 1; k < Block(q[i].r); k++) {
        ans[q[i].d] += s[k];
      }
      for (int k = Left(q[i].r); k <= q[i].r; k++) {
        ans[q[i].d] += a[k];
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
