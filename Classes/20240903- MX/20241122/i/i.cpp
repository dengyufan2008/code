#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 3e4 + 1, kMaxM = 15 + 1, kMod = 998244353, kInv2 = kMod + 1 >> 1;
int n, m, q, a[kMaxN];
LL f[kMaxM - 1][kMaxN][kMaxM];
int fwt[kMaxM][kMaxM][kMaxM], inv[kMaxM];
int trans[kMaxM][kMaxN][kMaxM][kMaxM];

class Seg1 {  // Dp 数组
 public:
  struct V {
    LL f[kMaxM];
  };

 private:
  V v[kMaxN << 2];
  int o;

  V Merge(V &x, V &y) {
    static V ans;
    for (int i = 0; i <= o; i++) {
      ans.f[i] = x.f[i] * y.f[i] % kMod;
    }
    return ans;
  }

  void Update(int p, int x) {
    for (int i = 0; i <= o; i++) {
      v[p].f[i] = f[o][x][i];
    }
  }

  void Init(int p, int l, int r) {
    if (l == r) {
      return Update(p, l);
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
    v[p] = Merge(v[p << 1], v[p << 1 | 1]);
  }

  void Update(int p, int l, int r, int x) {
    if (l == r) {
      return Update(p, x);
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Update(p << 1, l, mid, x);
    } else {
      Update(p << 1 | 1, mid + 1, r, x);
    }
    v[p] = Merge(v[p << 1], v[p << 1 | 1]);
  }

  V Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p];
    }
    int mid = l + r >> 1;
    if (mid >= _l && mid < _r) {
      V x = Ask(p << 1, l, mid, _l, _r);
      V y = Ask(p << 1 | 1, mid + 1, r, _l, _r);
      return Merge(x, y);
    } else if (mid >= _l) {
      return Ask(p << 1, l, mid, _l, _r);
    } else {
      return Ask(p << 1 | 1, mid + 1, r, _l, _r);
    }
  }

 public:
  void Init(int _o) { o = _o, Init(1, 1, n); }
  void Update(int x) { Update(1, 1, n, x); }
  V Ask(int l, int r) { return Ask(1, 1, n, l, r); }
} seg1[kMaxM - 1];

class Seg2 {  // =i 的连续段相关
 public:
  struct V {
    int s, c;   // =i 的数量, =i 的段数
    bool l, r;  // 左边是否是 =i, 右边是否是 =i
  };

 private:
  V v[kMaxN << 2];
  int o;

  V Merge(V &x, V &y) {
    static V ans;
    ans.s = x.s + y.s, ans.c = x.c + y.c - (x.r && y.l);
    ans.l = x.l, ans.r = y.r;
    return ans;
  }

  void Update(int p, int x) {
    v[p].s = v[p].c = v[p].l = v[p].r = a[x] == o;
  }

  void Init(int p, int l, int r) {
    if (l == r) {
      return Update(p, l);
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
    v[p] = Merge(v[p << 1], v[p << 1 | 1]);
  }

  void Update(int p, int l, int r, int x) {
    if (l == r) {
      return Update(p, x);
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Update(p << 1, l, mid, x);
    } else {
      Update(p << 1 | 1, mid + 1, r, x);
    }
    v[p] = Merge(v[p << 1], v[p << 1 | 1]);
  }

  V Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p];
    }
    int mid = l + r >> 1;
    if (mid >= _l && mid < _r) {
      V x = Ask(p << 1, l, mid, _l, _r);
      V y = Ask(p << 1 | 1, mid + 1, r, _l, _r);
      return Merge(x, y);
    } else if (mid >= _l) {
      return Ask(p << 1, l, mid, _l, _r);
    } else {
      return Ask(p << 1 | 1, mid + 1, r, _l, _r);
    }
  }

 public:
  void Init(int _o) { o = _o, Init(1, 1, n); }
  void Update(int x) { Update(1, 1, n, x); }
  V Ask(int l, int r) { return Ask(1, 1, n, l, r); }
} seg2[kMaxM - 1];

class Seg3 {  // >= i 的连续段相关
  int v[kMaxN << 2], o;

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p] = a[l] >= o;
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
    v[p] = v[p << 1] + v[p << 1 | 1];
  }

  void Update(int p, int l, int r, int x) {
    if (l == r) {
      v[p] = a[x] >= o;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Update(p << 1, l, mid, x);
    } else {
      Update(p << 1 | 1, mid + 1, r, x);
    }
    v[p] = v[p << 1] + v[p << 1 | 1];
  }

  int FindPre(int p, int l, int r) {
    if (v[p] == r - l + 1) {
      return 1;
    } else if (l == r) {
      return l + 1;
    }
    int mid = l + r >> 1;
    if (v[p << 1 | 1] == r - mid) {
      return FindPre(p << 1, l, mid);
    } else {
      return FindPre(p << 1 | 1, mid + 1, r);
    }
  }

  int FindPre(int p, int l, int r, int x) {
    if (r <= x) {
      return FindPre(p, l, r);
    }
    int mid = l + r >> 1, ans = 1;
    if (mid < x) {
      ans = FindPre(p << 1 | 1, mid + 1, r, x);
    }
    if (ans == 1) {
      ans = FindPre(p << 1, l, mid, x);
    }
    return ans;
  }

  int FindSuf(int p, int l, int r) {
    if (v[p] == r - l + 1) {
      return n;
    } else if (l == r) {
      return r - 1;
    }
    int mid = l + r >> 1;
    if (v[p << 1] == mid - l + 1) {
      return FindSuf(p << 1 | 1, mid + 1, r);
    } else {
      return FindSuf(p << 1, l, mid);
    }
  }

  int FindSuf(int p, int l, int r, int x) {
    if (l >= x) {
      return FindSuf(p, l, r);
    }
    int mid = l + r >> 1, ans = n;
    if (mid >= x) {
      ans = FindSuf(p << 1, l, mid, x);
    }
    if (ans == n) {
      ans = FindSuf(p << 1 | 1, mid + 1, r, x);
    }
    return ans;
  }

 public:
  void Init(int _o) { o = _o, Init(1, 1, n); }
  void Update(int x) { Update(1, 1, n, x); }
  int FindPre(int x) { return FindPre(1, 1, n, x); }
  int FindSuf(int x) { return FindSuf(1, 1, n, x); }
} seg3[kMaxM - 1];

void Init() {  // O(m^4+nm^3)
  static LL c[kMaxM][kMaxM] = {};
  for (int i = 0; i <= m; i++) {  // 计算组合数
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; j++) {
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % kMod;
    }
  }
  inv[0] = fwt[0][0][0] = 1;  // 计算 2^{-i} 以及在长度为 2^i 时 f_j 对 fwt_k 贡献的系数
  for (int i = 1; i <= m; i++) {
    inv[i] = 1LL * inv[i - 1] * kInv2 % kMod;
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k <= i; k++) {
        for (int l = max(j + k - i, 0); l <= min(j, k); l++) {
          LL w = c[k][l] * c[i - k][j - l] % kMod;
          if (l & 1) {
            fwt[i][j][k] = (fwt[i][j][k] - w + kMod) % kMod;
          } else {
            fwt[i][j][k] = (fwt[i][j][k] + w) % kMod;
          }
        }
      }
    }
  }
  trans[0][0][0][0] = 1;  // 计算 a_k 在经过 j 个 =i 的转移后对 a_l 贡献的系数
  for (int i = 1; i <= m; i++) {
    for (int j = 0; j <= i; j++) {
      trans[i][0][j][j] = 1;
    }
    for (int j = 1; j <= n; j++) {
      for (int k = 0; k <= i; k++) {
        int *f = trans[i][j][k], *g = trans[i][j - 1][k];
        for (int l = 0; l <= i; l++) {
          if (l == 0) {
            f[l] = 1LL * g[l + 1] * (i - l) % kMod;
          } else if (l == i) {
            f[l] = 1LL * g[l - 1] * l % kMod;
          } else {
            f[l] = (1LL * g[l - 1] * l + 1LL * g[l + 1] * (i - l)) % kMod;
          }
        }
      }
    }
  }
}

void Dp() {  // O(nm^3)
  static LL h[kMaxM] = {};
  for (int i = 0; i < m; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 0; k <= i; k++) {
        f[i][j][k] = 1;
      }
    }
  }
  for (int i = m - 1; i >= 0; i--) {
    for (int l = 1, r = 1; l <= n; l = r) {
      for (; r <= n && (a[l] >= i) == (a[r] >= i); r++) {
      }
      if (a[l] >= i) {
        for (int j = 0; j <= i + 1; j++) {
          h[j] = 1;
        }
        int c = (a[l] == i) + (r <= n && a[r - 1] == i);
        for (int p = l, q = l; p < r; p = q) {
          for (; q < r && (a[p] > i) == (a[q] > i); q++) {
          }
          if (a[p] > i) {
            for (int j = 0; j <= i + 1; j++) {  // 异或卷积上一层的 Dp 值
              h[j] = h[j] * f[i + 1][p][j] % kMod;
            }
          } else {
            c += q - p - 1;  // 累计没有被上一层覆盖的转移数量
          }
        }
        LL *g = f[i][l];
        for (int j = 0; j <= i + 1; j++) {  // 还原 fwt 数组
          g[j] = 0;
          for (int k = 0; k <= i + 1; k++) {
            g[j] = (g[j] + h[k] * fwt[i + 1][k][j]) % kMod;
          }
          g[j] = g[j] * inv[i + 1] % kMod;
        }
        for (int j = 0; j <= i + 1; j++) {  // 计算没有被上一层覆盖的转移
          h[j] = 0;
          for (int k = 0; k <= i + 1; k++) {
            h[j] = (h[j] + g[k] * trans[i + 1][c][k][j]) % kMod;
          }
        }
        for (int j = 0; j <= i + 1; j++) {
          g[j] = h[j];
        }
        if (r == n + 1) {  // 之后没有限制, 需要将 f[s|1<<i] 累加入 f[s]
          for (int j = 0; j <= i; j++) {
            g[j] = (g[j] + g[j + 1]) % kMod;
          }
        }
        for (int j = 0; j <= i; j++) {  // 进行 fwt
          h[j] = 0;
          for (int k = 0; k <= i; k++) {
            h[j] = (h[j] + g[k] * fwt[i][k][j]) % kMod;
          }
        }
        for (int j = 0; j <= i; j++) {
          g[j] = h[j];
        }
        g[i + 1] = 0;
      }
    }
  }
  for (int i = 0; i < m; i++) {
    seg1[i].Init(i), seg2[i].Init(i), seg3[i].Init(i);
  }
}

void ReDp(int i, int l, int r) {  // O(m^2+m\logn)
  static LL h[kMaxM];
  Seg1::V v1;
  if (i + 1 < m) {
    v1 = seg1[i + 1].Ask(l, r);  // 异或卷积上一层的 Dp 值
  } else {
    for (int j = 0; j <= m; j++) {
      v1.f[j] = 1;
    }
  }
  Seg2::V v2 = seg2[i].Ask(l, r);
  int c = v2.s - v2.c + (a[l] == i) + (r < n && a[r] == i);  // 累计没有被上一层覆盖的转移数量
  LL *g = f[i][l];
  for (int j = 0; j <= i + 1; j++) {  // 还原 fwt 数组
    g[j] = 0;
    for (int k = 0; k <= i + 1; k++) {
      g[j] = (g[j] + v1.f[k] * fwt[i + 1][k][j]) % kMod;
    }
    g[j] = g[j] * inv[i + 1] % kMod;
  }
  for (int j = 0; j <= i + 1; j++) {  // 计算没有被上一层覆盖的转移
    h[j] = 0;
    for (int k = 0; k <= i + 1; k++) {
      h[j] = (h[j] + g[k] * trans[i + 1][c][k][j]) % kMod;
    }
  }
  if (r == n) {  // 之后没有限制, 需要将 f[s|1<<i] 累加入 f[s]
    for (int j = 0; j <= i; j++) {
      h[j] = (h[j] + h[j + 1]) % kMod;
    }
  }
  for (int j = 0; j <= i; j++) {  // 进行 fwt
    g[j] = 0;
    for (int k = 0; k <= i; k++) {
      g[j] = (g[j] + h[k] * fwt[i][k][j]) % kMod;
    }
  }
  g[i + 1] = 0, seg1[i].Update(l);
}

void Change(int x, int y) {  // O(m^3+m^2\logn)
  if (a[x] == y) {
    return;
  }
  int z = a[x];
  a[x] = y, seg2[y].Update(x), seg2[z].Update(x);
  if (z < y) {
    for (int i = y; i > z; i--) {
      seg3[i].Update(x);
      int l = seg3[i].FindPre(x), r = seg3[i].FindSuf(x);
      if (r > x) {  // 删去 x+1 处的 Dp 值
        for (int j = 0; j <= i; j++) {
          f[i][x + 1][j] = 1;
        }
        seg1[i].Update(x + 1);
      }
      ReDp(i, l, r);
    }
    for (int i = z; i >= 0; i--) {
      int l = seg3[i].FindPre(x), r = seg3[i].FindSuf(x);
      ReDp(i, l, r);
    }
  } else {
    for (int i = z; i > y; i--) {
      int l = seg3[i].FindPre(x), r = seg3[i].FindSuf(x);
      seg3[i].Update(x);
      if (l < x) {
        ReDp(i, l, x - 1);
      } else {  // 删去 x 处的 Dp 值
        for (int j = 0; j <= i; j++) {
          f[i][x][j] = 1;
        }
        seg1[i].Update(x);
      }
      if (r > x) {
        ReDp(i, x + 1, r);
      }
    }
    for (int i = y; i >= 0; i--) {
      int l = seg3[i].FindPre(x), r = seg3[i].FindSuf(x);
      ReDp(i, l, r);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], a[i]--;
  }
  Init(), Dp();
  for (int i = 1, x, y; i <= q; i++) {
    cin >> x >> y, y--;
    Change(x, y);
    cout << f[0][1][0] << '\n';
  }
  return 0;
}
