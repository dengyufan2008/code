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
      cout << w + v[p] << " \n"[l == n];
      return;
    }
    int mid = l + r >> 1;
    Print(p << 1, l, mid, w + v[p]);
    Print(p << 1 | 1, mid + 1, r, w + v[p]);
  }

 public:
  void Add(int p, LL w) { v[p] += w; }
  void Print() { Print(1, 1, n, 0); }
} ans;
class Seg {
  struct Lst {
    int w, p, chk0, chk1;
    bool o;

    Lst() : w(0), p(0), chk0(kInf), chk1(-kInf), o(0) {}

    Lst(int _w, int _p, int _chk0, int _chk1, bool _o)
        : w(_w), p(_p), chk0(_chk0), chk1(_chk1), o(_o) {}

    Lst operator+(Lst x) {
      if (w > x.w || w == x.w && p < x.p) {
        return Lst(w, p, min(chk0, x.chk0), max(chk1, x.chk1), o);
      }
      return x;
    }
  };
  struct V {
    Lst lst;
    int chk0 = kInf, chk1 = -kInf;
    LL tag1, tag20, tag21;
    bool o;
  } v[kMaxN << 2];
  int p[kMaxN];

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p].lst.p = l, v[p].lst.o = q[l].o;
      q[l].o ? v[p].chk1 = q[l].w : v[p].chk0 = q[l].w;
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
  }

  void Tag20(int p, int l, int r, LL tag2) {  // CHICK
    ;
  }

  void Tag21(int p, int l, int r, LL tag2) {  // CHICK
    ;
  }

  void Tag1(int p, int l, int r, Lst lst, LL tag1) {  // CHICK
    if (l == r) {
      ;
    }
  }

  void Pushdown(int p, int l, int r) {  // CHICK
    int mid = l + r >> 1;
    if (v[p].tag1) {
      Tag1(p << 1 | 1, mid + 1, r, v[p << 1].lst, v[p].tag1);
      v[p].tag1 = 0;
    }
    if (v[p].tag20) {
      Tag20(p << 1 | 1, mid + 1, r, v[p].tag20);
      v[p].tag20 = 0;
    }
    if (v[p].tag21) {
      Tag21(p << 1 | 1, mid + 1, r, v[p].tag21);
      v[p].tag21 = 0;
    }
  }

  void Pushup(int p) {
    v[p].lst = Lst(), v[p].chk0 = kInf, v[p].chk1 = -kInf;
    if (v[p << 1].o && v[p << 1 | 1].o) {
      v[p].lst = v[p << 1].lst + v[p << 1 | 1].lst;
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

  void ChangeLst(int p, int l, int r, int d, int o = -1,
                 int lst, int chk0 = kInf, int chk1 = -kInf, bool forced) {
    if (l == r) {
      ~o && (v[p].o = o);
      if (forced || v[p].lst.w < lst) {
        v[p].lst.w = lst, v[p].lst.chk0 = chk0, v[p].lst.chk1 = chk1;
      }
      return;
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1;
    if (mid >= d) {
      ChangeLst(p << 1, l, mid, d, o, lst, chk0, chk1, forced);
    } else {
      if (lst <= l && v[p << 1].o) {
        chk0 = min(chk0, v[p << 1].chk0), chk1 = max(chk1, v[p << 1].chk1);
      }
      ChangeLst(p << 1 | 1, mid + 1, r, d, o, lst, chk0, chk1, forced);
    }
    Pushup(p);
  }

  void Recover(int p, int l, int r) {  // CHICK
    ;
  }

 public:
  void Init() { Init(1, 1, n); }
  void Tag() { Tag1(1, 1, n, Lst(), 1); }

  void Add(int d) {
    ChangeLst(1, 1, n, d, 1, CalcLst(1, 1, n, d), 1);
    (p[d] = FindP(1, 1, n, d)) ? ChangeLst(1, 1, n, p[d], d, 0) : void();
  }

  void Remove(int d) {
    ChangeLst(1, 1, n, d, 0, 0, 1);
    ChangeLst(1, 1, n, p[d], CalcLst(1, 1, n, p[d]), 1);
  }

  void Recover() { Recover(1, 1, n); }
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
      return seg.Tag();
    }
    int mid = l + r >> 1;
    Calc(p << 1, l, mid), Calc(p << 1 | 1, mid + 1, r);
    for (int i = v[p].size() - 1; i >= 0; i--) {
      seg.Remove(v[p][i]);
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
