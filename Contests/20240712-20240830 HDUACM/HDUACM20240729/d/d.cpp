#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 18, kMaxM = 10, kInf = 1e9;
int t, n, m, ans, a[kMaxN], w[1 << kMaxM];
int o[1 << kMaxM], lw[1 << kMaxM], rw[1 << kMaxM];
bool f[1 << kMaxM], g[1 << kMaxM];

void S(int x, int s, int ls, int rs) {
  if (x < n) {
    int _f[1 << kMaxM], _g[1 << kMaxM];
    for (int i = 0; i < 1 << m; i++) {
      _f[i] = f[i], _g[i] = g[i];
    }
    for (int i = 0; i < 1 << m; i++) {
      f[i ^ a[x]] |= _f[i];
    }
    S(x + 1, s | 1 << x, ls ^ a[x], rs);
    for (int i = 0; i < 1 << m; i++) {
      f[i] = _f[i], g[i ^ a[x]] |= _g[i];
    }
    S(x + 1, s, ls, rs ^ a[x]);
    for (int i = 0; i < 1 << m; i++) {
      g[i] = _g[i];
    }
  } else {
    int lw = -kInf, rw = -kInf;
    for (int i = 0; i < 1 << m; i++) {
      if (f[o[i]] && w[o[i]] >= w[o[i] ^ ls]) {
        lw = max(lw, w[o[i] ^ ls]);
      }
      if (g[o[i]] && w[o[i]] >= w[o[i] ^ rs]) {
        rw = max(rw, w[o[i] ^ rs]);
        ans = min(ans, w[o[i]] - min(w[o[i] ^ rs], lw));
      }
      if (f[o[i]] && w[o[i]] >= w[o[i] ^ ls]) {
        ans = min(ans, w[o[i]] - min(w[o[i] ^ ls], rw));
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    ans = kInf, cin >> n >> m;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    for (int i = 0; i < 1 << m; i++) {
      cin >> w[i], o[i] = i;
    }
    sort(o, o + (1 << m), [](int i, int j) {
      return w[i] < w[j];
    });
    fill(&f[1], &f[1 << m], 0), fill(&g[1], &g[1 << m], 0);
    f[0] = g[0] = f[a[0]] = 1, S(1, 1, a[0], 0);
    cout << ans << '\n';
  }
  return 0;
}
