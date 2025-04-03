#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 2e5 + 1, kMaxL = 18, kMod = 998244353;
struct Q {
  int l, r, o;
} q1[kMaxN], q2[kMaxN];
int n, m, p[kMaxN], b[kMaxN];
bool a[kMaxN];
LL f[kMaxN];

struct A {
  LL w[2][2];

  A() {
    w[0][0] = 1, w[0][1] = 0, w[1][0] = 0, w[1][1] = 1;
  }

  A(LL w00, LL w01, LL w10, LL w11) {
    w[0][0] = w00, w[0][1] = w01, w[1][0] = w10, w[1][1] = w11;
  }

  A operator*(A a) {
    A ans = {0, 0, 0, 0};
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          ans.w[i][j] = (ans.w[i][j] + w[i][k] * a.w[k][j]) % kMod;
        }
      }
    }
    return ans;
  }
} ans[kMaxN];

class Seg {
  struct V {
    A a;
    bool t;
  } v[kMaxN << 2];

  void Init(int p, int l, int r) {
    v[p].a = {0, 1, 0, 1}, v[p].t = 0;
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
  }

  void Tag(int p) {
    v[p].a = {1, 0, 0, 1}, v[p].t = 1;
  }

  void Pushdown(int p) {
    if (v[p].t) {
      v[p].t = 0, Tag(p << 1), Tag(p << 1 | 1);
    }
  }

  void Clear(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return Tag(p);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Clear(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      Clear(p << 1 | 1, mid + 1, r, _l, _r);
    }
    v[p].a = v[p << 1].a * v[p << 1 | 1].a;
  }

  void Change(int p, int l, int r, int x, A y) {
    if (l == r) {
      v[p].a = y;
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, y);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, y);
    }
    v[p].a = v[p << 1].a * v[p << 1 | 1].a;
  }

  A Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p].a;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    A ans = {1, 0, 0, 1};
    if (mid >= _l) {
      ans = ans * Ask(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      ans = ans * Ask(p << 1 | 1, mid + 1, r, _l, _r);
    }
    return ans;
  }

 public:
  void Init() { Init(1, 1, n); }
  void Clear(int l, int r) { Clear(1, 1, n, l, r); }
  void Change(int x, A y) { Change(1, 1, n, x, y); }
  A Ask(int l, int r) { return Ask(1, 1, n, l, r); }
} seg;

void Input() {
  static int d[kMaxL][kMaxN];
  static string s;
  cin >> s, n = s.size(), s = '~' + s;
  for (int i = 1; i <= n; i++) {
    a[i] = s[i] == '(';
    b[i] = b[i - 1] + (a[i] ? 1 : -1);
    d[0][i] = i;
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 0; j <= n; j++) {
      d[i][j] = d[i - 1][j];
      if (j + (1 << i - 1) <= n) {
        if (b[d[i][j]] > b[d[i - 1][j + (1 << i - 1)]]) {
          d[i][j] = d[i - 1][j + (1 << i - 1)];
        }
      }
    }
  }
  cin >> m;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y;
    int o = 31 - __builtin_clz(y - x + 1);
    if (b[d[o][x]] > b[d[o][y - (1 << o) + 1]]) {
      z = d[o][y - (1 << o) + 1];
    } else {
      z = d[o][x];
    }
    q1[i] = {x + 1, z, i}, q2[i] = {z + 1, y, i};
  }
}

void CalcP() {
  static vector<int> l;
  for (int i = 1; i <= n; i++) {
    if (a[i]) {
      l.push_back(i);
    } else if (!l.empty()) {
      p[l.back()] = i, p[i] = l.back(), l.pop_back();
    }
  }
}

void Dp(int l, int r) {
  LL f0 = 0, f1 = 1;  // 上一个是不是进入, 默认是的
  for (int i = l + 1; i < r; i = p[i] + 1) {
    Dp(i, p[i]);
    LL _f0 = (f0 * 2 + f1) % kMod;
    LL _f1 = (f0 + f1) * f[i] % kMod;
    f0 = _f0, f1 = _f1;
  }
  f[l] = f[r] = (f0 + f1) % kMod;
}

void Dp() {
  for (int i = 1; i <= n; i++) {
    if (p[i]) {
      Dp(i, p[i]), i = p[i];
    }
  }
}

void Solve1() {
  sort(q1 + 1, q1 + m + 1, [](Q i, Q j) {
    return i.l > j.l;
  });
  seg.Init();
  for (int i = n, j = 1; i >= 1; i--) {
    if (a[i] && p[i]) {
      seg.Clear(i, p[i]);
      seg.Change(i, {2, f[i], 1, f[i]});
    }
    for (; j <= m && q1[j].l == i; j++) {
      if (i <= q1[j].r) {
        ans[q1[j].o] = ans[q1[j].o] * seg.Ask(i, q1[j].r);
      }
    }
  }
}

void Solve2() {
  sort(q2 + 1, q2 + m + 1, [](Q i, Q j) {
    return i.r < j.r;
  });
  seg.Init();
  for (int i = 1, j = 1; i <= n; i++) {
    if (!a[i] && p[i]) {
      seg.Clear(p[i], i);
      seg.Change(i, {2, f[i], 1, f[i]});
    }
    for (; j <= m && q2[j].r == i; j++) {
      if (q2[j].l <= i) {
        ans[q2[j].o] = ans[q2[j].o] * seg.Ask(q2[j].l, i);
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), CalcP(), Dp(), Solve1(), Solve2();
  for (int i = 1; i <= m; i++) {
    cout << (ans[i].w[1][0] + ans[i].w[1][1]) % kMod << '\n';
  }
  return 0;
}
