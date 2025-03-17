#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1, kMaxL = 18, kInf = 2e9;
struct V {
  int w, mn, mx;          // 初始的合法情况
  int c, s[2], f[kMaxL];  // 子树大小, 两个儿子, 父亲的 st 表
  int r1, r2, l;          // 中序遍历, 重链剖分遍历, 重链链顶
  bool o;                 // 重儿子
} v[kMaxN];
int n, m, a1[kMaxN], a2[kMaxN];

class Seg1 {  // 判断区间是否不降
  struct V {
    int mn, mx;
    bool o;
  } v[kMaxN << 2];

  void Pushup(int p) {
    v[p].mn = min(v[p << 1].mn, v[p << 1 | 1].mn);
    v[p].mx = max(v[p << 1].mx, v[p << 1 | 1].mx);
    v[p].o = v[p << 1].o && v[p << 1 | 1].o && v[p << 1].mx <= v[p << 1 | 1].mn;
  }

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p].mn = v[p].mx = ::v[a1[l]].w, v[p].o = 1;
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
    Pushup(p);
  }

  void Change(int p, int l, int r, int x, int w) {
    if (l == r) {
      v[p].mn = v[p].mx = w;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, w);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, w);
    }
    Pushup(p);
  }

  int FindPre(int p, int l, int r, int &w) {
    if (l == r) {
      return l + 1;
    }
    int mid = l + r >> 1;
    if (v[p << 1 | 1].o && v[p << 1 | 1].mx <= w) {
      return FindPre(p << 1, l, mid, w = v[p << 1 | 1].mn);
    } else {
      return FindPre(p << 1 | 1, mid + 1, r, w);
    }
  }

  int FindPre(int p, int l, int r, int x, int &w) {
    if (r <= x) {
      if (v[p].o && v[p].mx <= w) {
        w = v[p].mn;
        return l;
      } else {
        return FindPre(p, l, r, w);
      }
    }
    int mid = l + r >> 1, ans = mid + 1;
    if (mid < x) {
      ans = FindPre(p << 1 | 1, mid + 1, r, x, w);
    }
    if (ans == mid + 1) {
      ans = FindPre(p << 1, l, mid, x, w);
    }
    return ans;
  }

  int FindNxt(int p, int l, int r, int &w) {
    if (l == r) {
      return l - 1;
    }
    int mid = l + r >> 1;
    if (v[p << 1].o && v[p << 1].mn >= w) {
      return FindNxt(p << 1 | 1, mid + 1, r, w = v[p << 1].mx);
    } else {
      return FindNxt(p << 1, l, mid, w);
    }
  }

  int FindNxt(int p, int l, int r, int x, int &w) {
    if (l >= x) {
      if (v[p].o && v[p].mn >= w) {
        w = v[p].mx;
        return r;
      } else {
        return FindNxt(p, l, r, w);
      }
    }
    int mid = l + r >> 1, ans = mid;
    if (mid >= x) {
      ans = FindNxt(p << 1, l, mid, x, w);
    }
    if (ans == mid) {
      ans = FindNxt(p << 1 | 1, mid + 1, r, x, w);
    }
    return ans;
  }

 public:
  void Init() { Init(1, 1, n); }
  void Change(int x, int w) { Change(1, 1, n, x, w); }
  int FindPre(int x) {
    int w = kInf;
    return FindPre(1, 1, n, x, w);
  }
  int FindNxt(int x) {
    int w = -kInf;
    return FindNxt(1, 1, n, x, w);
  }
} seg1;

class Seg2 {  // 统计答案
  struct V {
    int c, t;
  } v[kMaxN << 2];

  void Init(int p, int l, int r) {
    v[p].t = -1;
    if (l == r) {
      v[p].c = ::v[a2[l]].mn <= ::v[a2[l]].mx;
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
    v[p].c = v[p << 1].c + v[p << 1 | 1].c;
  }

  void Tag(int p, int l, int r, bool o) {
    v[p].c = o ? r - l + 1 : 0, v[p].t = o;
  }

  void Pushdown(int p, int l, int r) {
    if (v[p].t != -1) {
      int mid = l + r >> 1;
      Tag(p << 1, l, mid, v[p].t);
      Tag(p << 1 | 1, mid + 1, r, v[p].t);
      v[p].t = -1;
    }
  }

  void Change(int p, int l, int r, int _l, int _r, bool o) {
    if (l >= _l && r <= _r) {
      return Tag(p, l, r, o);
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Change(p << 1, l, mid, _l, _r, o);
    }
    if (mid < _r) {
      Change(p << 1 | 1, mid + 1, r, _l, _r, o);
    }
    v[p].c = v[p << 1].c + v[p << 1 | 1].c;
  }

 public:
  void Init() { Init(1, 1, n); }
  void Change(int l, int r, bool o) { Change(1, 1, n, l, r, o); }
  int Ask() { return v[1].c; }
} seg2;

void Init(int x) {
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  int l = v[x].s[0], r = v[x].s[1];
  l ? v[l].f[0] = x, Init(l) : void();
  r ? v[r].f[0] = x, Init(r) : void();
  v[x].c = v[v[x].s[0]].c + v[v[x].s[1]].c + 1;
  v[x].o = v[v[x].s[0]].c < v[v[x].s[1]].c;
}

void CalcR1(int x) {
  static int k = 0;
  v[x].s[0] ? CalcR1(v[x].s[0]) : void();
  v[x].r1 = ++k, a1[k] = x;
  v[x].s[1] ? CalcR1(v[x].s[1]) : void();
}

void CalcR2(int x, int l) {
  static int k = 0;
  bool o = v[x].o;
  v[x].r2 = ++k, a2[k] = x, v[x].l = l;
  v[x].s[o] ? CalcR2(v[x].s[o], l) : void();
  v[x].s[!o] ? CalcR2(v[x].s[!o], v[x].s[!o]) : void();
}

void CalcW(int x) {
  int l = v[x].s[0], r = v[x].s[1];
  l ? CalcW(l) : void();
  r ? CalcW(r) : void();
  if ((!l || v[x].w >= v[l].mx && v[l].mn <= v[l].mx) &&
      (!r || v[x].w <= v[r].mn && v[r].mn <= v[r].mx)) {
    v[x].mn = l ? v[l].mn : v[x].w;
    v[x].mx = r ? v[r].mx : v[x].w;
  } else {
    v[x].mn = kInf, v[x].mx = -kInf;
  }
}

int Find(int x, int l, int r) {
  for (int i = kMaxL - 1; i >= 0; i--) {
    int y = v[x].f[i];
    if (y && v[y].r1 - v[v[y].s[0]].c >= l && v[y].r1 + v[v[y].s[1]].c <= r) {
      x = y;
    }
  }
  return x;
}

void Change(int x, int y, bool o) {
  for (; v[x].l != v[y].l; x = v[v[x].l].f[0]) {
    seg2.Change(v[v[x].l].r2, v[x].r2, o);
  }
  seg2.Change(v[y].r2, v[x].r2, o);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].s[0] >> v[i].s[1];
  }
  Init(1), CalcR1(1), CalcR2(1, 1);
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w;
  }
  CalcW(1), seg1.Init(), seg2.Init();
  for (int i = 1, x, w; i <= m; i++) {
    cin >> x >> w;
    seg1.Change(v[x].r1, w);
    int l = seg1.FindPre(v[x].r1);
    int r = seg1.FindNxt(v[x].r1);
    if (v[x].r1 - v[v[x].s[0]].c >= l && v[x].r1 + v[v[x].s[1]].c <= r) {
      int y = Find(x, l, r);
      Change(x, y, 1);
      v[y].f[0] ? Change(v[y].f[0], 1, 0) : void();
    } else {
      Change(x, 1, 0);
    }
    cout << seg2.Ask() << '\n';
  }
  return 0;
}
