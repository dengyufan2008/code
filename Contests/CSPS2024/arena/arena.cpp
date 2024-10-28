#include <fstream>
#define LL long long

using namespace std;

ifstream cin("arena.in");
ofstream cout("arena.out");

const int kMaxN = 1e5 + 1, kMaxM = 1 << 18;
struct V {
  int d;   // 到叶子经过的边数
  int w;   // 是定义点时的值, 与 k 取 min
  int t;   // [0, t) 为未定义点, [t, n) 为定义点
  int f;   // [0, f) 父链上所有点为未定义点
  int p;   // 父链上自己当擂主的最靠近叶子的点
  int l;   // [0, l) 父链上右边的兄弟当擂主赢的都还是未定义点
  bool r;  // 父链上左边的兄弟当擂主时是否都输了
  bool o;
} v[kMaxM];
int t, n, m, k, s, a[kMaxN], q[kMaxN];
LL ans[kMaxN];

void Init() {
  for (int i = s; i < s << 1; i++) {
    v[i].d = 0;
    v[i].w = min(a[i - s], k);
    v[i].t = i - s;
  }
  for (int i = s - 1; i >= 1; i--) {
    v[i].d = v[i << 1].d + 1;
    if (v[i << 1 | v[i].o].w >= v[i].d) {
      v[i].w = v[i << 1 | v[i].o].w;
      v[i].t = v[i << 1 | v[i].o].t;
    } else {
      v[i].w = v[i << 1 | v[i].o ^ 1].w;
      v[i].t = max(v[i << 1].t, v[i << 1 | 1].t);
    }
  }
  v[1].f = v[1].t, v[1].p = 1, v[1].l = s, v[1].r = 1;
  for (int i = 2; i < s << 1; i++) {
    v[i].f = v[i >> 1].f, v[i].p = v[i >> 1].p;
    v[i].l = v[i >> 1].l, v[i].r = v[i >> 1].r;
    v[i].f = min(v[i].f, v[i].t);
    if ((i & 1) == v[i >> 1].o) {
      v[i].p = i;
    }
    if ((i & 1 ^ 1) && v[i >> 1].o && v[i + 1].w > v[i].d) {
      v[i].l = min(v[i].l, v[i + 1].t);
    }
    if (v[i].r && (i & 1) && !v[i >> 1].o) {
      v[i].r = v[i - 1].w <= v[i].d;
    }
  }
}

void Solve() {
  Init();
  for (int i = 0; i <= n; i++) {
    ans[i] = 0;
  }
  for (int i = 0; i < n; i++) {  // 作为定义点时的贡献
    int p = v[i + s >> min(a[i], k)].p;
    if ((p & -p) == p && v[i + s].r) {
      int r = min(v[i + s].l, s / p);
      if (i < r) {
        ans[i] += i + 1, ans[min(r, n)] -= i + 1;
      }
    }
  }
  for (int i = 1, j = 1; i < s; i++) {  // 作为未定义点时的贡献
    for (; 1 << j <= i; j++) {
    }
    if (1 << j - 1 < v[i + s].f) {
      ans[1 << j - 1] += i + 1, ans[min(v[i + s].f, n)] -= i + 1;
    }
  }
  for (int i = 1; i < n; i++) {
    ans[i] += ans[i - 1];
  }
  LL u = 0;
  for (int i = 1; i <= m; i++) {
    u ^= i * ans[q[i]];
  }
  cout << u << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i], q[i]--;
  }
  for (; 1 << k < n; k++) {
  }
  s = 1 << k;
  for (int i = k; i >= 1; i--) {
    for (int j = 1 << i - 1; j < 1 << i; j++) {
      static char c;
      cin >> c, v[j].o = c == '1';
    }
  }
  cin >> t;
  for (int i = 1, x[4]; i <= t; i++) {
    cin >> x[0] >> x[1] >> x[2] >> x[3];
    for (int j = 0; j < n; j++) {
      a[j] ^= x[j + 1 & 3];
    }
    Solve();
    for (int j = 0; j < n; j++) {
      a[j] ^= x[j + 1 & 3];
    }
  }
  return 0;
}
