#include <fstream>
#define LL long long

using namespace std;

ifstream cin("ds.in");
ofstream cout("ds.out");

const int kMaxN = 1e5 + 1;
struct A {
  LL w, l;
};
struct V {
  A even0, even1, odd0, odd1;
  LL t;
} v[kMaxN << 2];
int t, n, m, a[kMaxN];

A Max(A x, A y) {
  if (x.w > y.w || x.w == y.w && x.l < y.l) {
    return x;
  }
  return y;
}

A Merge(A x, A y) {
  return {x.w + y.w, x.l + y.l};
}

void Pushup(int p) {
  V &x = v[p], l = v[p << 1], r = v[p << 1 | 1];
  x.even0 = Max(Max(l.even0, r.even0), Max(Merge(l.even0, r.even0), Merge(l.odd0, r.odd1)));
  x.even1 = Max(Max(l.even1, r.even1), Max(Merge(l.even1, r.even1), Merge(l.odd1, r.odd0)));
  x.odd0 = Max(Max(l.odd0, r.odd0), Max(Merge(l.even0, r.odd0), Merge(l.odd0, r.even1)));
  x.odd1 = Max(Max(l.odd1, r.odd1), Max(Merge(l.odd1, r.even0), Merge(l.even1, r.odd1)));
}

void Tag(int p, int k) {
  v[p].odd0.w -= k, v[p].odd1.w += k, v[p].t += k;
}

void Pushdown(int p) {
  if (v[p].t) {
    Tag(p << 1, v[p].t), Tag(p << 1 | 1, v[p].t);
    v[p].t = 0;
  }
}

void Init(int p, int l, int r) {
  v[p].t = 0;
  if (l == r) {
    v[p].even0 = v[p].even1 = {0, 0}, v[p].odd0 = {-a[l], 1}, v[p].odd1 = {a[l], 1};
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
  Pushup(p);
}

void Add(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    Tag(p, k);
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(p << 1, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Add(p << 1 | 1, mid + 1, r, _l, _r, k);
  }
  Pushup(p);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    Init(1, 1, n);
    for (int i = 1, o, x, y, z; i <= m; i++) {
      cin >> o;
      if (o) {
        cout << v[1].even0.w << ' ' << v[1].even0.l << '\n';
      } else {
        cin >> x >> y >> z;
        Add(1, 1, n, x, y, z);
      }
    }
  }
  return 0;
}
