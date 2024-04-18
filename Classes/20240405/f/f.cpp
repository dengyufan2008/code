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
    int w, p;
    bool o;
    bool operator<(const Lst &x) const {
      return w > x.w || w == x.w && p < x.p;
    }
  };
  struct V {
    Lst lst;
    int chk[2] = {kInf, -kInf};
    LL tag1, tag2;
    bool o;
  } v[kMaxN << 2];
  int p[kMaxN];

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p].lst.p = l, v[p].lst.o = q[l].o;
      v[p].chk[q[l].o] = q[l].w;
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
  }

  void Tag1(int p, LL w) { v[p].tag1 += w; }

  void Pushdown(int p) {  // CHICK
    ;
  }

  void Pushup(int p) {  // CHICK
    ;
  }

  bool Check(int p, int d) {
    ;
  }

  int FindP(int p, int l, int r, int d) {  // CHICK
    if (!Check(p, d)) {
      return 0;
    } else if (l == r) {
      return l;
    }
    int mid = l + r >> 1;
    if (mid > d) {
      int t = FindP(p << 1, l, mid, d);
      return t ? t : FindP(p << 1 | 1, mid + 1, r, d);
    } else if (mid < d + 1) {
      return FindP(p << 1 | 1, mid + 1, r, d);
    }
  }

  int CalcLst(int p, int l, int r, int d) {  // CHICK
    ;
  }

  void ChangeLst(int p, int l, int r, int d, int lst, bool o) {  // CHICK
    ;
  }

  void Add(int p, int l, int r, int d, int lst) {
    if (l == r) {
      v[p].lst.w = lst, v[p].o = 1;
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= d) {
      Add(p << 1, l, mid, d, lst);
    } else {
      Add(p << 1 | 1, mid + 1, r, d, lst);
    }
    Pushup(p);
  }

  void Remove(int p, int l, int r, int d) {
    if (l == r) {
      v[p].o = 0;
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= d) {
      Remove(p << 1, l, mid, d);
    } else {
      Remove(p << 1 | 1, mid + 1, r, d);
    }
    Pushup(p);
  }

  void Recover(int p, int l, int r) {  // CHICK
    ;
  }

 public:
  void Init() { Init(1, 1, n); }
  void Tag() { Tag1(1, 1); }

  void Add(int d) {
    Add(1, 1, n, d, CalcLst(1, 1, n, d));
    (p[d] = FindP(1, 1, n, d)) ? ChangeLst(1, 1, n, p[d], d, 0) : void();
  }

  void Remove(int d) {
    Remove(1, 1, n, d);
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
