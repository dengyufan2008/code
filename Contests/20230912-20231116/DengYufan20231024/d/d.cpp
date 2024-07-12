#include <fstream>
#include <vector>
#define Uint unsigned

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 1e5 + 1;

struct E {
  struct A {
    Uint c1, ci, ck, cik;
  };
  struct S {
    Uint sl, sli, slk, slik;
  } pos, neg;
  Uint k, s, ls, rs, ll, rl;
  int ltype, rtype;
  bool same;
  vector<A> h;
  E operator+(E e) {
    E ans;
    if (rtype == 1 && e.ltype == 1) {
      ans.pos.sl = pos.sl + e.pos.sl - rs * rl - e.ls * e.ll + (rs + e.ls) * (rl + e.ll);
      ans.pos.sli = pos.sli + e.pos.sli + e.pos.sl * (k - 1) - rs * rl * k - e.ls * e.ll * k + (rs + e.ls) * (rl + e.ll) * k;
    }
  }
};
struct V {
  E e;
  int type, x;
  V operator+(V v) {
    return {e + v.e, 0, 0};
  }
} v[kMaxN << 2];
Uint n, m, a[kMaxN];

void Init(int p, int l, int r) {
  if (l == r) {
    Uint x = a[l];
    if (x > 0) {
      v[p] = {{{x, x, x, x}, {0, 0, 0, 0}, 1, x, x, x, 1, 1, 1, 1, 1, {}}, 0, 0};
    } else {
      v[p] = {{{0, 0, 0, 0}, {x, x, x, x}, 0, -x, x, x, 1, 1, -1, -1, 1, {}}, 0, 0};
    }
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
  v[p] = v[p << 1] + v[p << 1 | 1];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    a[i] = x;
  }
  Init(1, 1, n);
  for (int o, x, y, z; m--;) {
    cin >> o >> x >> y;
    if (o == 1) {
      cin >> z;
    } else if (o == 2) {
      cin >> z;
    } else if (o == 3) {
      cin >> z;
    } else if (o == 4) {
      cin >> z;
    } else {
      ;
    }
  }
  return 0;
}
