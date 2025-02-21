#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e5 + 1, kMaxM = kMaxN << 1, kMaxL = 10;
const int kMod = 998244353, kInv2 = kMod + 1 >> 1;
struct E {
  LL mul = 1, add;  // 自己的 Dp 值为重儿子的 Dp 值乘 mul 再加 add
  E() : mul(1), add(0) {}
  E(LL _mul, LL _add) : mul(_mul), add(_add) {}
  E operator+(E e) {
    return {mul * e.mul % kMod, (add * e.mul + e.add) % kMod};
  }
  E operator+=(E e) {
    mul = mul * e.mul % kMod, add = (add * e.mul + e.add) % kMod;
    return *this;
  }
};
struct V {
  int f, l, e[kMaxL];
  int s, r, t, b;   // t: 链顶 b: 链底
  int _f, _l;       // 当前的 f 与 l
  LL w[kMaxL + 2];  // 轻儿子与自己的背包
  vector<int> g;
} v[kMaxM];
int n, m, _m, a[kMaxN], b[kMaxN], c[kMaxN];
LL pw[kMaxM], fact[kMaxL + 2];
string s;

class Seg {
  E v[kMaxM << 2];

  void Change(int p, int l, int r, int x, E e) {
    if (l == r) {
      v[p] = e;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, e);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, e);
    }
    v[p] = v[p << 1 | 1] + v[p << 1];
  }

  E Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p];
    }
    int mid = l + r >> 1;
    E ans = {1, 0};
    if (mid < _r) {
      ans += Ask(p << 1 | 1, mid + 1, r, _l, _r);
    }
    if (mid >= _l) {
      ans += Ask(p << 1, l, mid, _l, _r);
    }
    return ans;
  }

 public:
  void Change(int x, E e) { Change(1, 1, m, x, e); }
  E Ask(int l, int r) { return Ask(1, 1, m, l, r); }
} seg;

void Insert(int x) {
  static int r = 1;
  int p = r;
  v[++m].l = v[r].l + 1;
  for (; p && !v[p].e[x]; p = v[p].f) {
    v[p].e[x] = m;
  }
  if (p) {
    int q = v[p].e[x];
    if (v[p].l + 1 == v[q].l) {
      v[m].f = q, r = m;
    } else {
      b[v[m].l] = q, c[v[m].l] = v[p].l + 1;  // CHICK
      v[++m] = v[q], v[m].l = v[p].l + 1;
      for (; p && v[p].e[x] == q; p = v[p].f) {
        v[p].e[x] = m;
      }
      v[m - 1].f = v[q].f = m, r = m - 1;
    }
  } else {
    v[m].f = 1, r = m;
  }
  a[v[r].l] = v[r].f;  // CHICK
}

void Init1(int x) {
  v[x].s = 1;
  for (int &i : v[x].g) {
    Init1(i), v[x].s += v[i].s;
    if (v[i].s > v[v[x].g[0]].s) {
      swap(i, v[x].g[0]);
    }
  }
}

void Init2(int x, int t) {
  static int k = 0;
  v[x].t = t, v[x].r = ++k;
  if (v[x].g.empty()) {
    v[x].b = x;
    return;
  }
  Init2(v[x].g[0], t);
  for (int i : v[x].g) {
    if (i != v[x].g[0]) {
      Init2(i, i);
    }
  }
  v[x].b = v[v[x].g[0]].b;
}

void CalcTag(int, bool);

void UpdateDp(int x, E e) {  // 修改 x 的 e, 并更新祖先链上的 w, mul, add; O(\log n (\log n + kMaxL))
  for (int i = v[x].t, j = v[i].f; j; i = v[j].t, j = v[i].f) {
    if (j <= _m) {
      LL w = kMod - seg.Ask(v[i].r, v[v[i].b].r).add;
      for (int k = 0; k < v[j].g.size(); k++) {
        v[j].w[k + 1] = (v[j].w[k + 1] + v[j].w[k] * w) % kMod;
      }
    }
  }
  seg.Change(v[x].r, e);
  for (int i = v[x].t, j = v[i].f; j; i = v[j].t, j = v[i].f) {
    if (j <= _m) {
      LL w = seg.Ask(v[i].r, v[v[i].b].r).add;
      for (int k = v[j].g.size() - 1; k >= 0; k--) {
        v[j].w[k + 1] = (v[j].w[k + 1] + v[j].w[k] * w) % kMod;
      }
      CalcTag(j, 0);
    } else {
      seg.Change(v[j].r, seg.Ask(v[i].r, v[v[i].b].r));
    }
  }
}

void CalcTag(int x, bool o) {  // calc mul, add; 0/1: Update or not; O(\log n (\log n + kMaxL))
  E e = {};
  for (int i = v[x].g.empty() ? 1 : v[x].g.size(); i >= 1; i--) {
    e.mul = (e.mul + v[x].w[i] * fact[i + 1]) % kMod;
    e.add = (e.add + v[x].w[i] * fact[i]) % kMod;
  }
  int _l = v[x]._l - v[v[x]._f]._l - 1;
  e += (E){pw[_l], (pw[_l] - 1) * kInv2 % kMod};
  o ? UpdateDp(x, e) : seg.Change(v[x].r, e);
}

void CalcW(int x) {  // calc w; O((\log n + kMaxL)^2)
  v[x].w[0] = v[x].w[1] = 1;
  for (int i = 2; i <= v[x].g.size() + 1; i++) {
    v[x].w[i] = 0;
  }
  for (int i = 1; i < v[x].g.size(); i++) {
    LL w = seg.Ask(v[v[x].g[i]].r, v[v[v[x].g[i]].b].r).add;
    for (int j = i; j >= 0; j--) {
      v[x].w[j + 1] = (v[x].w[j + 1] + v[x].w[j] * w) % kMod;
    }
  }
  CalcTag(x, 1);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0] = 1;
  for (int i = 1; i < kMaxM; i++) {
    pw[i] = pw[i - 1] * 3 % kMod;
  }
  fact[0] = 1;
  for (int i = 1; i < kMaxL + 2; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  v[0].l = v[0]._l = -1;
  cin >> s, n = s.size(), m = _m = 1, s = '~' + s;
  for (int i = 1; i <= n; i++) {
    Insert(s[i] - 'a');
  }
  for (int i = 2; i <= m; i++) {
    v[v[i].f].g.push_back(i);
  }
  Init1(1), Init2(1, 1), v[1].w[0] = 1;
  for (int i = 1; i <= n; i++) {  // O(n (\log n + kMaxL)^2)
    if (b[i]) {
      _m += 2, v[_m]._f = v[b[i]]._f, v[_m]._l = c[i];
      v[b[i]]._f = _m, CalcTag(b[i], 1);

      int __m = _m - 1;
      v[__m]._f = a[i], v[__m]._l = i, v[__m].w[0] = v[__m].w[1] = 1;
      int _l = v[__m]._l - v[a[i]]._l - 1;
      UpdateDp(__m, (E){3, 1} + (E){pw[_l], (pw[_l] - 1) * kInv2 % kMod});

      CalcW(_m);
    } else {
      _m++, v[_m]._f = a[i], v[_m]._l = i, v[_m].w[0] = v[_m].w[1] = 1;
      int _l = v[_m]._l - v[a[i]]._l - 1;
      UpdateDp(_m, (E){3, 1} + (E){pw[_l], (pw[_l] - 1) * kInv2 % kMod});
    }
    cout << seg.Ask(1, v[v[1].b].r).add << " \n"[i == n];
  }
  return 0;
}
