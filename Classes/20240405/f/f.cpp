#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 1e5 + 1;
int n, m;
struct Q {
  int d, w;
  bool o;
};
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
    int chk[2];
    LL tag1, tag2;
    bool o;
  } v[kMaxN << 2];

 public:
  void Tag1(int p, LL w) { v[p].tag1 += w; }

 private:
 public:
  void Change(Q q, bool o) {
  }
  void Recover() {
  }
} seg;
class Op {
  vector<Q> v[kMaxN << 2];

  void Add(int p, int l, int r, int _l, int _r, Q q) {
    if (l >= _l && r <= _r) {
      return v[p].push_back(q);
    }
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, q);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, q);
    }
  }

  void Calc(int p, int l, int r) {
    for (Q i : v[p]) {
      seg.Change(i, 1);
    }
    if (l == r) {
      return seg.Tag1(1, 1);
    }
    int mid = l + r >> 1;
    Calc(p << 1, l, mid), Calc(p << 1 | 1, mid + 1, r);
    for (Q i : v[p]) {
      seg.Change(i, 0);
    }
  }

 public:
  void Add(int l, int r, int d, int w, bool o) {
    Add(1, 1, n, l, r, {d, w, o});
  }

  void Calc() { Calc(1, 1, n), seg.Recover(); }
} op;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, o, x, y, z; i <= m; i++) {
    cin >> o >> x >> y >> z;
    op.Add(x, y, i, z, o == 1);
  }
  op.Calc(), ans.Print();
  return 0;
}
