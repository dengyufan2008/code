#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 31, kMaxV = 5, kMaxM = kMaxN * kMaxV * kMaxV;
struct A {
  int c, w, k;
} a[kMaxN];
int n, m, r;
LL ans;
bool e[kMaxN][kMaxN], g[kMaxN][kMaxN];

class Knapsack {
  LL f[kMaxN][kMaxM];
  vector<A> v;

 public:
  void Add(A a) {
    int t = v.size();
    v.push_back(a);
    for (int i = 0; i < kMaxM; i++) {
      f[t + 1][i] = 0;
    }
    for (int i = 0; i < kMaxM; i++) {
      for (int j = 0, _i = i; j <= min(a.k, kMaxV) && _i < kMaxM; j++, _i += a.c) {
        f[t + 1][_i] = max(f[t + 1][_i], f[t][i] + 1LL * a.w * j);
      }
    }
  }

  void Del() { v.pop_back(); }

  LL Calc() {
    static int l[kMaxN];
    int t = v.size();
    LL ans = 0;
    for (int i = 0; i < t; i++) {
      l[i] = i;
    }
    sort(l, l + t, [&](int i, int j) {
      return 1LL * v[i].w * v[j].c > 1LL * v[j].w * v[i].c;
    });
    int _r = 0;
    for (int i = 0, s = 0; i < t; i++) {
      A a = v[l[i]];
      int k = max(a.k - kMaxV, 0);
      if (s + 1LL * a.c * a.k <= r) {
        _r += a.c * k;
        s += a.c * a.k;
        ans += 1LL * a.w * k;
      } else {
        int _k = max(min((r - s) / a.c, a.k) - kMaxV, 0);
        _r += a.c * _k;
        ans += 1LL * a.w * _k;
        return ans + f[t][r - _r];
      }
    }
    return ans + f[t][min(r - _r, kMaxM - 1)];
  }
} kk;

void S(int x) {
  if (x == n) {
    ans = max(ans, kk.Calc());
    return;
  } else if (!e[x][n] && !g[x][n]) {
    return;
  }
  for (int i = x + 1; i <= n; i++) {
    if (e[x][i] && !g[x][i]) {
      kk.Add(a[i]), S(i), kk.Del();
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> r;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].c >> a[i].w >> a[i].k;
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, e[x][y] = 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      for (int k = i + 1; k < j; k++) {
        g[i][j] |= (g[i][k] || e[i][k]) && (g[k][j] || e[k][j]);
      }
    }
  }
  ans = -1, kk.Add(a[1]), S(1);
  cout << ans << '\n';
  return 0;
}
