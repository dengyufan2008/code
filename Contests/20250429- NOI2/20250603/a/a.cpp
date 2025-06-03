#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 10, kMaxM = 59049, kInf = 114514, kMod = 998244353;
struct F {
  int c, s;
} ans, f[kMaxM], g[kMaxM];
int t, n, m, pw[kMaxN + 1];

void Update(F &x, F y) {
  if (x.c > y.c) {
    x = y;
  } else if (x.c == y.c) {
    x.s += y.s, x.s >= kMod && (x.s -= kMod);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0] = 1;
  for (int i = 1; i <= kMaxN; i++) {
    pw[i] = pw[i - 1] * 3;
  }
  fill(&g[0], &g[kMaxM], F{kInf, 0});
  cin >> t;
  while (t--) {
    cin >> n >> m;
    fill(&f[0], &f[pw[m]], F{kInf, 0});
    for (int s = 0; s < pw[m]; s++) {
      bool o = 1;
      for (int j = 0; j < m; j++) {
        o &= s / pw[j] % 3 != 2;
      }
      if (o) {
        f[s] = {0, 1};
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        static char c;
        cin >> c;
        for (int s = 0; s < pw[m]; s++) {
          int u = s % 3, l = s / pw[m - 1] % 3;
          bool o = (c == '1') ^ (u == 2) ^ (j && l == 2);
          int t0 = s / 3 + o * pw[m - 1];
          int t1 = s / 3 + 2 * pw[m - 1];
          int t2 = s / 3 + !o * pw[m - 1];
          if (j && l != 2) {
            l ? t1 -= pw[m - 2] : t1 += pw[m - 2];
          }
          if (u != 1) {
            Update(g[t0], f[s]);
            Update(g[t2], {f[s].c + 2, f[s].s});
          }
          if (u != 0) {
            Update(g[t1], {f[s].c + 1, f[s].s});
          }
        }
        for (int s = 0; s < pw[m]; s++) {
          f[s] = g[s], g[s] = {kInf, 0};
        }
      }
    }
    ans = {kInf, 0};
    for (int s = 0; s < pw[m]; s++) {
      bool o = 1;
      for (int j = 0; j < m; j++) {
        o &= s / pw[j] % 3 != 1;
      }
      if (o) {
        Update(ans, f[s]);
      }
    }
    cout << ans.c << ' ' << ans.s << '\n';
  }
  return 0;
}
