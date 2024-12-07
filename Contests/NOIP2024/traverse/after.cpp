#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("traverse.in");
ofstream cout("traverse.out");

const int kMaxN = 1e5 + 1, kMod = 1e9 + 7;
struct V {
  int d;          // dep
  bool b;         // 是否是选定的边
  LL f[2], g[2];  // f: 半条链 g:一条链 0:没有给定的边 1:无所谓
  vector<int> e;
} v[kMaxN];
int t, n, m, r;
LL inv[kMaxN], fact[kMaxN];

void CalcD(int f, int x) {
  v[x].d = v[f].d + 1;
  for (int i : v[x].e) {
    if (i != f) {
      CalcD(x, i);
    }
  }
}

void Dp(int f, int x) {
  if (v[x].e.size() == 1) {
    v[x].f[0] = v[x].f[1] = 1;
    return;
  }
  LL w = inv[v[x].e.size() - 1];
  for (int i : v[x].e) {
    if (i != f) {
      Dp(x, i);
      v[x].g[1] = (v[x].g[1] + v[i].g[1] + v[x].f[1] * v[i].f[1]) % kMod;
      v[x].f[1] = (v[x].f[1] + v[i].f[1] * w) % kMod;
      if (v[i].b) {
        v[x].g[0] = (v[x].g[0] + v[i].g[0]) % kMod;
      } else {
        v[x].g[0] = (v[x].g[0] + v[i].g[0] + v[x].f[0] * v[i].f[0]) % kMod;
        v[x].f[0] = (v[x].f[0] + v[i].f[0] * w) % kMod;
      }
    }
  }
}

void Solve() {
  static pair<int, int> e[kMaxN];
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    v[i] = v[0];
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y, e[i] = {x, y};
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  if (n <= 2) {
    for (int i = 1, o; i <= m; i++) {
      cin >> o;
    }
    cout << 1 << '\n';
    return;
  }
  for (r = 1; v[r].e.size() == 1; r++) {
  }
  CalcD(0, r);
  for (int i = 1, o; i <= m; i++) {
    cin >> o;
    int x = e[o].first, y = e[o].second;
    v[x].d < v[y].d ? swap(x, y) : void();
    v[x].b = 1;
  }
  Dp(0, r);
  LL ans = (v[r].g[1] - v[r].g[0] + kMod) % kMod;
  for (int i = 1; i <= n; i++) {
    ans = ans * fact[v[i].e.size() - 1] % kMod;
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  inv[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    inv[i] = kMod - (kMod / i) * inv[kMod % i] % kMod;
  }
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  cin >> t >> t;
  while (t--) {
    Solve();
  }
  return 0;
}
