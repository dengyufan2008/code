#include <fstream>
#include <vector>
#define LL long long
#define LLL __int128_t

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 2e5 + 2;
const LL kInf = 1e18;
struct Pair {
  LL x, y;
} q[kMaxN];
int n, m, l[kMaxN], _l[kMaxN];
LL a[kMaxN];
bool b[kMaxN];
vector<int> v[kMaxN];
class Cov {
  int t, p = 1;
  Pair v[kMaxN];

  LLL Cross(Pair o, Pair x, Pair y) {
    return LLL(x.x - o.x) * (y.y - o.y) - LLL(x.y - o.y) * (y.x - o.x);
  }

 public:
  void Clear() { t = 0, p = 1; }

  void Insert(Pair x) {
    for (; t >= 1 && v[t].y == x.y && v[t].x >= x.x ||
           t >= 2 && Cross(v[t - 1], v[t], x) <= 0;
         t--) {
    }
    v[++t] = x;
  }

  LL Ask(int x) {
    for (; p < t && (v[p].y - v[p + 1].y) * x >= v[p + 1].x - v[p].x; p++) {
    }
    return p <= t ? v[p].x + v[p].y * x : kInf;
  }
} cov;
class Seg1 {
  struct V {
    LL s, t, c;
  } v[kMaxN << 2];

  void Tag(int p, LL t) {
    v[p].s += v[p].c * t;
    v[p].t += t;
  }

  void Pushdown(int p) {
    if (v[p].t) {
      Tag(p << 1, v[p].t);
      Tag(p << 1 | 1, v[p].t);
      v[p].t = 0;
    }
  }

  void Pushup(int p) {
    v[p].s = v[p << 1].s + v[p << 1 | 1].s;
    v[p].c = v[p << 1].c + v[p << 1 | 1].c;
  }

  void Init(int p, int l, int r) {
    if (l == r) {
      return v[p].s = a[l], v[p].c = l, void();
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
    Pushup(p);
  }

  LL Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p].s;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    LL ans = 0;
    if (mid >= _l) {
      ans += Ask(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      ans += Ask(p << 1 | 1, mid + 1, r, _l, _r);
    }
    return ans;
  }

  void Delete(int p, int l, int r, int x) {
    if (l == r) {
      return v[p].s = v[p].c = 0, void();
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      Delete(p << 1, l, mid, x);
    } else {
      Delete(p << 1 | 1, mid + 1, r, x);
    }
    Pushup(p);
  }

 public:
  void Init() { Init(1, 1, n); }
  void Tag() { Tag(1, 1); }
  void Delete(int x) { Delete(1, 1, n, x); }
  LL Ask(int l, int r) { return Ask(1, 1, n, l, r); }
} seg1;
class Seg2 {
  struct V {
    LL s, c, w = kInf, t1, t2 = -1;
    int b;
  } v[kMaxN << 2];

  void Tag1(int p, int r, LL t1) {
    v[p].s += v[p].c * t1;
    v[p].w += r * t1, v[p].t1 += t1;
  }

  void Tag2(int p, LL t2) {
    v[p].s = v[p].b * t2;
    v[p].w = v[p].t2 = t2, v[p].t1 = 0;
  }

  void Pushdown(int p, int l, int r) {
    int mid = l + r >> 1;
    if (~v[p].t2) {
      Tag2(p << 1, v[p].t2);
      Tag2(p << 1 | 1, v[p].t2);
      v[p].t2 = -1;
    }
    if (v[p].t1) {
      Tag1(p << 1, mid, v[p].t1);
      Tag1(p << 1 | 1, r, v[p].t1);
      v[p].t1 = 0;
    }
  }

  void Pushup(int p) {
    v[p].s = v[p << 1].s + v[p << 1 | 1].s;
    v[p].c = v[p << 1].c + v[p << 1 | 1].c;
    v[p].w = v[p << 1 | 1].w;
    v[p].b = v[p << 1].b + v[p << 1 | 1].b;
  }

  int Find(int p, int l, int r, LL x) {
    if (l == r) {
      return l + (v[p].w <= x);
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1;
    if (v[p << 1].w > x) {
      return Find(p << 1, l, mid, x);
    } else {
      return Find(p << 1 | 1, mid + 1, r, x);
    }
  }

  void Fill(int p, int l, int r, int x, LL y) {
    if (l >= x) {
      return Tag2(p, y);
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1;
    if (mid >= x) {
      Fill(p << 1, l, mid, x, y);
    }
    Fill(p << 1 | 1, mid + 1, r, x, y);
    Pushup(p);
  }

  void Enable(int p, int l, int r, int x) {
    if (l == r) {
      return v[p].b = 1, v[p].c = l, v[p].s = v[p].w, void();
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1;
    if (mid >= x) {
      Enable(p << 1, l, mid, x);
    } else {
      Enable(p << 1 | 1, mid + 1, r, x);
    }
    Pushup(p);
  }

  LL Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p].s;
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1;
    LL ans = 0;
    if (mid >= _l) {
      ans += Ask(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      ans += Ask(p << 1 | 1, mid + 1, r, _l, _r);
    }
    return ans;
  }

 public:
  void CheckMin(LL x) {
    int l = Find(1, 1, n, x);
    l <= n ? Fill(1, 1, n, l, x) : void();
  }

  void Enable(int x) { Enable(1, 1, n, x); }
  void Tag() { Tag1(1, n, 1); }
  LL Ask(int l, int r) { return Ask(1, 1, n, l, r); }
} seg2;

void Solve(int nl, int nr, int ml, int mr) {
  if (nl > nr) {
    return;
  } else if (ml == mr) {
    for (int i = nl; i <= nr; i++) {
      v[ml].push_back(l[i]);
    }
    return;
  }
  int nmid = nl, mmid = ml + mr >> 1;
  cov.Clear();
  for (int i = ml; i <= mmid; i++) {
    if (q[i].y <= 0) {
      cov.Insert(q[i]);
    }
  }
  for (int i = nl; i <= nr; i++) {
    if (a[l[i]] >= cov.Ask(l[i])) {
      nmid++, b[i] = 1;
    } else {
      b[i] = 0;
    }
  }
  for (int i = nl, j = nl, k = nmid; i <= nr; i++) {
    _l[b[i] ? j++ : k++] = l[i];
  }
  for (int i = nl; i <= nr; i++) {
    l[i] = _l[i];
  }
  Solve(nl, nmid - 1, ml, mmid), Solve(nmid, nr, mmid + 1, mr);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], l[i] = i;
  }
  for (int i = 1, o; i <= m; i++) {
    cin >> o;
    if (o == 1) {
      cin >> q[i].x, q[i].y = q[m + 1].y;
    } else if (o == 2) {
      q[i].x = -1, q[i].y = 114514, q[m + 1].y--;
    } else {
      cin >> q[i].x >> q[i].y;
    }
  }
  Solve(1, n, 1, m + 1), seg1.Init();
  for (int i = 1; i <= m; i++) {
    if (q[i].y <= 0) {
      seg2.CheckMin(q[i].x);
      for (int j : v[i]) {
        seg1.Delete(j), seg2.Enable(j);
      }
    } else if (q[i].x <= 0) {
      seg1.Tag(), seg2.Tag();
    } else {
      cout << seg1.Ask(q[i].x, q[i].y) + seg2.Ask(q[i].x, q[i].y) << '\n';
    }
  }
  return 0;
}
