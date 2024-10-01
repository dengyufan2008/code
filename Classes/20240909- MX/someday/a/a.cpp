#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e5 + 1;
struct E {
  int x, y;
  LL w;
} e[kMaxN];
struct V {
  int h, l, r;
  LL d;
  vector<pair<int, LL>> e;
} v[kMaxN];
struct D {
  LL mx, mn, l, r, lr, t;
} d[kMaxN << 3];
int n, m;
LL k;
vector<int> a;

void T(int f, int x) {
  v[x].h = v[f].h + 1, v[x].l = v[x].r = a.size(), a.push_back(x);
  for (auto i : v[x].e) {
    if (i.first != f) {
      v[i.first].d = v[x].d + i.second;
      T(x, i.first);
      v[x].r = a.size(), a.push_back(x);
    }
  }
}

void Pushup(int p) {
  d[p].mx = max(d[p << 1].mx, d[p << 1 | 1].mx);
  d[p].mn = min(d[p << 1].mn, d[p << 1 | 1].mn);
  d[p].l = max(d[p << 1].l, d[p << 1 | 1].l);
  d[p].l = max(d[p].l, d[p << 1].mx - (d[p << 1 | 1].mn << 1));
  d[p].r = max(d[p << 1].r, d[p << 1 | 1].r);
  d[p].r = max(d[p].r, d[p << 1 | 1].mx - (d[p << 1].mn << 1));
  d[p].lr = max(d[p << 1].lr, d[p << 1 | 1].lr);
  d[p].lr = max(d[p].lr, d[p << 1].mx + d[p << 1 | 1].r);
  d[p].lr = max(d[p].lr, d[p << 1].l + d[p << 1 | 1].mx);
}

void Tag(int p, LL t) {
  d[p].mx += t, d[p].mn += t, d[p].l -= t, d[p].r -= t, d[p].t += t;
}

void Pushdown(int p) {
  Tag(p << 1, d[p].t), Tag(p << 1 | 1, d[p].t), d[p].t = 0;
}

void Init(int p, int l, int r) {
  if (l == r) {
    return Tag(p, v[a[l]].d);
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
  Pushup(p);
}

void Add(int p, int l, int r, int _l, int _r, LL w) {
  if (l >= _l && r <= _r) {
    return Tag(p, w);
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(p << 1, l, mid, _l, _r, w);
  }
  if (mid < _r) {
    Add(p << 1 | 1, mid + 1, r, _l, _r, w);
  }
  Pushup(p);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k;
  for (int i = 1; i < n; i++) {
    cin >> e[i].x >> e[i].y >> e[i].w;
    v[e[i].x].e.push_back({e[i].y, e[i].w});
    v[e[i].y].e.push_back({e[i].x, e[i].w});
  }
  a.resize(1), T(0, 1);
  for (int i = 1; i < n; i++) {
    v[e[i].x].h < v[e[i].y].h ? swap(e[i].x, e[i].y) : void();
  }
  Init(1, 1, (n << 1) - 1);
  for (int i = 1, x; i <= m; i++) {
    static long long w, ans = 0;
    cin >> x >> w;
    x = (x + ans) % (n - 1) + 1, w = (w + ans) % k;
    Add(1, 1, (n << 1) - 1, v[e[x].x].l, v[e[x].x].r, w - e[x].w);
    e[x].w = w;
    cout << (ans = d[1].lr) << '\n';
  }
  return 0;
}
