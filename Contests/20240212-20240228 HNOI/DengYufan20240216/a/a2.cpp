#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const int kMaxN = 201, kMod = 1e9 + 7;
struct V {
  int d, f, s;
  LL w;
  vector<int> e;
} v[kMaxN];
int n, s, l[kMaxN];
LL w, ans, inv[kMaxN], g[kMaxN][kMaxN];

void S(int f, int x) {
  static int k = 0;
  v[x].d = v[f].d + 1, v[x].f = f, v[x].s = 1, l[x] = x;
  for (int i : v[x].e) {
    if (i != f) {
      S(x, i);
      v[x].s += v[i].s;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  inv[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    inv[i] = (kMod - kMod / i) * inv[kMod % i] % kMod;
  }
  cin >> n >> s;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  S(0, s), v[0].w = 1, w = inv[n];
  sort(l + 1, l + n + 1, [](int i, int j) {
    return v[i].d < v[j].d;
  });
  for (int i = 1; i <= n; i++) {
    int x = l[i], f = v[x].f;
    v[x].w = v[f].w * v[x].s % kMod * inv[v[x].s - 1] % kMod;
    w = w * x % kMod * inv[v[x].s] % kMod;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (v[i].f == v[j].f) {
        g[i][j] = g[j][i] = v[v[i].f].w * inv[v[i].s + v[j].s - 1] % kMod;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int x = l[i], fx = v[x].f, y = l[j], fy = v[y].f;
      if (fx != fy) {
        g[x][y] = g[y][x] = (g[fx][y] * v[fx].s + g[x][fy] * v[fy].s) % kMod * inv[v[x].s + v[y].s - 1] % kMod;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (i != s) {
      ans = (ans + w * v[i].s % kMod * v[v[i].f].w % kMod * abs(i - v[i].f)) % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      ans = (ans + g[i][j] * w % kMod * v[i].s % kMod * v[j].s % kMod * abs(i - j)) % kMod;
    }
  }
  cout << ans << '\n';
  return 0;
}
