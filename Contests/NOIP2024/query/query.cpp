#include <fstream>
#include <vector>

using namespace std;

ifstream cin("query.in");
ofstream cout("query.out");

const int kMaxN = 5e5 + 1, kMaxL = 19;
struct V {
  int d, r, f[kMaxL];
  vector<int> e;
} v[kMaxN];
int n, m, k, a[kMaxN], lg[kMaxN];
int mn[kMaxL][kMaxN], mx[kMaxL][kMaxN];

void T(int f, int x) {
  v[x].d = v[f].d + 1, v[x].r = ++k, a[k] = x, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i);
    }
  }
}

int Lca(int x, int y) {
  v[x].d < v[y].d ? swap(x, y) : void();
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = v[x].f[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? x : v[x].f[0];
}

int Min(int l, int r) {
  int o = lg[r - l + 1];
  return min(mn[o][l], mn[o][r - (1 << o) + 1]);
}

int Max(int l, int r) {
  int o = lg[r - l + 1];
  return max(mx[o][l], mx[o][r - (1 << o) + 1]);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, 1);
  for (int i = 1; i <= n; i++) {
    mn[0][i] = mx[0][i] = v[i].r;
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      mn[i][j] = mn[i - 1][j], mx[i][j] = mx[i - 1][j];
      if (j + (1 << i - 1) <= n) {
        mn[i][j] = min(mn[i][j], mn[i - 1][j + (1 << i - 1)]);
        mx[i][j] = max(mx[i][j], mx[i - 1][j + (1 << i - 1)]);
      }
    }
  }
  cin >> m;
  for (int i = 1, l, r, x, ans; i <= m; i++) {
    cin >> l >> r >> x, ans = 0;
    for (int j = l; j + x - 1 <= r; j++) {
      int p = Min(j, j + x - 1), q = Max(j, j + x - 1);
      ans = max(ans, v[Lca(a[p], a[q])].d);
    }
    cout << ans << '\n';
  }
  return 0;
}
