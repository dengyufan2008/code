#include <fstream>

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 2e4 + 1, kMaxM = 2.5e4 + 1;
const int kMaxS = 59049, kMaxL = 11, kInf = 1e9;
struct E {
  int p, d;
} e[kMaxM << 1];
struct V {
  int w, d, et;
} v[kMaxN];
int n, m, p, ans, pw[kMaxL];
int f[kMaxS], g[kMaxS];
// 0:not able 1:able 2:chosen

bool Check(int s, int l, int r) {
  for (int i = l - 1; i < r; i++) {
    if (s / pw[i] % 3 == 0) {
      return 0;
    }
  }
  return 1;
}

void T(int x, int d) {
  v[x].d = d, fill(&g[0], &g[pw[d]], kInf);
  for (int s = 0; s < pw[p]; s++) {
    if (f[s] < kInf && Check(s, d, p)) {
      int o = 0, t = s % pw[d - 1];
      for (int i = v[x].et; i; i = e[i].p) {
        if (v[e[i].d].d && s / pw[v[e[i].d].d - 1] % 3 == 2) {
          o = 1;
          break;
        }
      }
      if (o) {
        t += pw[v[x].d - 1], g[t] = min(g[t], f[s]), t += pw[v[x].d - 1];
      } else {
        g[t] = min(g[t], f[s]), t += pw[v[x].d - 1] << 1;
      }
      for (int i = v[x].et; i; i = e[i].p) {
        if (v[e[i].d].d && s / pw[v[e[i].d].d - 1] % 3 == 0) {
          t += pw[v[e[i].d].d - 1];
        }
      }
      g[t] = min(g[t], f[s] + v[x].w);
    }
  }
  p = d, copy(&g[0], &g[pw[d]], &f[0]);
  for (int i = v[x].et; i; i = e[i].p) {
    if (!v[e[i].d].d) {
      T(e[i].d, d + 1);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0] = 1;
  for (int i = 1; i < kMaxL; i++) {
    pw[i] = pw[i - 1] * 3;
  }
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w;
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    e[i * 2 - 1] = {v[x].et, y}, v[x].et = i * 2 - 1;
    e[i * 2] = {v[y].et, x}, v[y].et = i * 2;
  }
  for (int i = 1; i <= n; i++) {
    !v[i].d ? T(i, 1) : void();
  }
  ans = kInf;
  for (int s = 0; s < pw[p]; s++) {
    if (Check(s, 1, p)) {
      ans = min(ans, f[s]);
    }
  }
  cout << ans << '\n';
  return 0;
}
