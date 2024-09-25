#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 1e5 + 1, kInf = 1e9;
int n, m;
struct Q {
  int w;
  bool o;
} q[kMaxN];
class Ans {
  LL v[kMaxN << 2];

  void Print(int p, int l, int r, LL w) {
    if (l == r) {
      cout << w + v[p] << " \n"[l == m];
      return;
    }
    int mid = l + r >> 1;
    Print(p << 1, l, mid, w + v[p]);
    Print(p << 1 | 1, mid + 1, r, w + v[p]);
  }

 public:
  void Add(int p, LL w) { v[p] += w; }

  void Print() { Print(1, 1, m, 0); }
} ans;
class Seg {
  struct Lst {
    int w, p, chk0, chk1;
    bool o;

    Lst() : w(0), p(0), chk0(kInf), chk1(-kInf), o(0) {}

    Lst(int _w, int _p, int _chk0, int _chk1, bool _o)
        : w(_w), p(_p), chk0(_chk0), chk1(_chk1), o(_o) {}

    LL Calc() { return 1LL * w * (o ? chk1 : chk0); }

    bool operator<(Lst x) { return w < x.w || w == x.w && p > x.p; }
  };
  struct V {
    Lst lst;
    int chk0, chk1;
    LL tag1, tag20, tag21;
    bool o;
  } v[kMaxN << 2];
  struct E {
    int d;
    Lst lst;
    bool o;
  };
  vector<E> e;

  Lst Merge(Lst x, int y) {
    if (x < v[y].lst) {
      return v[y].lst;
    } else if (v[y].o) {
      x.chk0 = min(x.chk0, v[y].chk0);
      x.chk1 = max(x.chk1, v[y].chk1);
    }
    return x;
  }

  void Init(int p, int l, int r) {
    v[p].chk0 = kInf, v[p].chk1 = -kInf;
    if (l == r) {
      v[p].lst.p = l, v[p].lst.o = q[l].o;
      q[l].o ? v[p].chk1 = q[l].w : v[p].chk0 = q[l].w;
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
  }

  void Tag20(int p, int l, int r, int chk0, LL tag20) {
    if (!tag20) {
      return;
    } else if (l == r) {
      return ans.Add(p, tag20 * (v[p].o ? min(chk0, v[p].chk0) : chk0));
    }
    int mid = l + r >> 1;
    if (!v[p << 1].o || v[p << 1].chk0 > chk0) {
      ans.Add(p << 1, tag20 * chk0);
      Tag20(p << 1 | 1, mid + 1, r, chk0, tag20);
    } else {
      Tag20(p << 1, l, mid, chk0, tag20);
      v[p].tag20 += tag20;
    }
  }

  void Tag21(int p, int l, int r, int chk1, LL tag21) {
    if (!tag21) {
      return;
    } else if (l == r) {
      return ans.Add(p, tag21 * (v[p].o ? max(chk1, v[p].chk1) : chk1));
    }
    int mid = l + r >> 1;
    if (!v[p << 1].o || v[p << 1].chk1 < chk1) {
      ans.Add(p << 1, tag21 * chk1);
      Tag21(p << 1 | 1, mid + 1, r, chk1, tag21);
    } else {
      Tag21(p << 1, l, mid, chk1, tag21);
      v[p].tag21 += tag21;
    }
  }

  void Tag1(int p, int l, int r, Lst lst, bool o, LL tag1) {
    if (!tag1) {
      return;
    } else if (l == r) {
      return ans.Add(p, tag1 * (v[p].o ? Merge(lst, p).Calc() : lst.Calc()));
    }
    int mid = l + r >> 1;
    if (o && (!v[p << 1].o || v[p << 1].lst < lst)) {
      if (lst.o) {
        Tag21(p << 1, l, mid, lst.chk1, tag1 * lst.w);
      } else {
        Tag20(p << 1, l, mid, lst.chk0, tag1 * lst.w);
      }
      Tag1(p << 1 | 1, mid + 1, r, Merge(lst, p << 1), o || v[p << 1].o, tag1);
    } else {
      Tag1(p << 1, l, mid, lst, o, tag1);
      v[p].tag1 += tag1;
    }
  }

  void Pushdown(int p, int l, int r) {
    int mid = l + r >> 1;
    if (v[p].tag20) {
      Tag20(p << 1 | 1, mid + 1, r, v[p << 1].chk0, v[p].tag20);
      v[p].tag20 = 0;
    }
    if (v[p].tag21) {
      Tag21(p << 1 | 1, mid + 1, r, v[p << 1].chk1, v[p].tag21);
      v[p].tag21 = 0;
    }
    if (v[p].tag1) {
      Tag1(p << 1 | 1, mid + 1, r, v[p << 1].lst, v[p << 1].o, v[p].tag1);
      v[p].tag1 = 0;
    }
  }

  void Pushup(int p) {
    v[p].lst = Lst(), v[p].chk0 = kInf, v[p].chk1 = -kInf;
    v[p].o = v[p << 1].o || v[p << 1 | 1].o;
    if (v[p << 1].o && v[p << 1 | 1].o) {
      v[p].lst = Merge(v[p << 1].lst, p << 1 | 1);
      v[p].chk0 = min(v[p << 1].chk0, v[p << 1 | 1].chk0);
      v[p].chk1 = max(v[p << 1].chk1, v[p << 1 | 1].chk1);
    } else if (v[p << 1].o) {
      v[p].lst = v[p << 1].lst;
      v[p].chk0 = v[p << 1].chk0;
      v[p].chk1 = v[p << 1].chk1;
    } else if (v[p << 1 | 1].o) {
      v[p].lst = v[p << 1 | 1].lst;
      v[p].chk0 = v[p << 1 | 1].chk0;
      v[p].chk1 = v[p << 1 | 1].chk1;
    }
  }

  bool Check(int p, int d) {
    return v[p].o && (q[d].o ? v[p].chk0 <= q[d].w : v[p].chk1 >= q[d].w);
  }

  int FindP(int p, int l, int r, int d) {
    if (!Check(p, d)) {
      return 0;
    } else if (l == r) {
      return l;
    }
    int mid = l + r >> 1;
    if (mid > d) {
      int t = FindP(p << 1, l, mid, d);
      return t ? t : FindP(p << 1 | 1, mid + 1, r, d);
    } else {
      return FindP(p << 1 | 1, mid + 1, r, d);
    }
  }

  int CalcLst(int p, int l, int r, int d) {
    if (!Check(p, d)) {
      return 0;
    } else if (l == r) {
      return l;
    }
    int mid = l + r >> 1;
    if (mid >= d - 1) {
      return CalcLst(p << 1, l, mid, d);
    } else {
      int t = CalcLst(p << 1 | 1, mid + 1, r, d);
      return t ? t : CalcLst(p << 1, l, mid, d);
    }
  }

  void ChangeLst(int p, int l, int r, int d, int o,
                 int lst, int chk0, int chk1, bool forced) {
    if (l == r) {
      e.push_back({d, v[p].lst, v[p].o});
      if (o == 0) {
        v[p].o = 0, v[p].lst = Lst(0, l, chk0, chk1, q[l].o);
      } else {
        v[p].o |= o == 1;
        if (forced || v[p].lst.w < lst) {
          v[p].lst.w = lst;
          v[p].lst.chk0 = min(chk0, v[p].chk0);
          v[p].lst.chk1 = max(chk1, v[p].chk1);
        }
      }
      return;
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1;
    if (mid >= d) {
      ChangeLst(p << 1, l, mid, d, o, lst, chk0, chk1, forced);
    } else {
      if (lst < l && v[p << 1].o) {
        chk0 = min(chk0, v[p << 1].chk0), chk1 = max(chk1, v[p << 1].chk1);
      }
      ChangeLst(p << 1 | 1, mid + 1, r, d, o, lst, chk0, chk1, forced);
    }
    Pushup(p);
  }

  void ChangeLst(int p, int l, int r, int d, int o, Lst lst) {
    if (l == r) {
      v[p].o = o, v[p].lst = lst;
      return;
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1;
    if (mid >= d) {
      ChangeLst(p << 1, l, mid, d, o, lst);
    } else {
      ChangeLst(p << 1 | 1, mid + 1, r, d, o, lst);
    }
    Pushup(p);
  }

  void Recover(int p, int l, int r) {
    if (l < r) {
      Pushdown(p, l, r);
      int mid = l + r >> 1;
      Recover(p << 1, l, mid), Recover(p << 1 | 1, mid + 1, r);
    }
  }

 public:
  void Init() { Init(1, 1, m); }

  void Tag() { Tag1(1, 1, m, Lst(), 0, 1); }

  void Add(int d) {
    int lst = CalcLst(1, 1, m, d);
    ChangeLst(1, 1, m, d, 1, lst, kInf, -kInf, 1);
    int p = FindP(1, 1, m, d);
    if (p) {
      ChangeLst(1, 1, m, p, -1, d, kInf, -kInf, 0);
    } else {
      e.push_back({});
    }
  }

  void Undo() {
    for (int i = 0; i < 2; i++) {
      if (e.back().d) {
        ChangeLst(1, 1, m, e.back().d, e.back().o, e.back().lst);
      }
      e.pop_back();
    }
  }

  void Recover() { Recover(1, 1, m); }
} seg;
class Op {
  vector<int> v[kMaxN << 2];

  void Add(int p, int l, int r, int _l, int _r, int d) {
    if (l >= _l && r <= _r) {
      return v[p].push_back(d);
    }
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, d);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, d);
    }
  }

  void Calc(int p, int l, int r) {
    for (int i : v[p]) {
      seg.Add(i);
    }
    if (l == r) {
      seg.Tag();
    } else {
      int mid = l + r >> 1;
      Calc(p << 1, l, mid), Calc(p << 1 | 1, mid + 1, r);
    }
    for (int i : v[p]) {
      seg.Undo();
    }
  }

 public:
  void Add(int l, int r, int d) { Add(1, 1, n, l, r, d); }

  void Calc() { Calc(1, 1, n), seg.Recover(); }
} op;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, o, x, y, z; i <= m; i++) {
    cin >> o >> x >> y >> z;
    q[i] = {z, o == 1}, op.Add(x, y, i);
  }
  seg.Init(), op.Calc(), ans.Print();
  return 0;
}
