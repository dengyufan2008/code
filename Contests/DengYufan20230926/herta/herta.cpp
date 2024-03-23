#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("herta.in");
ofstream cout("herta.out");

const LL kMaxN = 2e5 + 1, kMaxM = 17;
struct V {
  LL w, d, f[kMaxM];
  vector<LL> e;
} v[2][kMaxN];
LL t, n, q, l[2], r[2];
unsigned LL w;

void T(LL f, LL x, bool o) {
  v[o][x].d = v[o][f].d + 1, v[o][x].f[0] = f;
  for (LL i = 1; i < kMaxM; i++) {
    v[o][x].f[i] = v[o][v[o][x].f[i - 1]].f[i - 1];
  }
  for (LL i : v[o][x].e) {
    if (i != f) {
      T(x, i, o);
    }
  }
}

LL Lca(LL x, LL y, bool o) {
  if (v[o][x].d < v[o][y].d) {
    swap(x, y);
  }
  for (LL i = kMaxM - 1; i >= 0; i--) {
    if (v[o][x].d - (1 << i) >= v[o][y].d) {
      x = v[o][x].f[i];
    }
  }
  for (LL i = kMaxM - 1; i >= 0; i--) {
    if (v[o][x].f[i] != v[o][y].f[i]) {
      x = v[o][x].f[i], y = v[o][y].f[i];
    }
  }
  return x == y ? x : v[o][x].f[0];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> t;
  while (t--) {
    w = 0;
    cin >> n >> q >> l[1] >> r[1];
    for (LL o = 0; o < 2; o++) {
      for (LL i = 2, x; i <= n; i++) {
        cin >> x;
        v[o][x].e.push_back(i);
      }
      for (LL i = 1; i <= n; i++) {
        cin >> v[o][i].w;
      }
    }
    T(0, 1, 0), T(0, 1, 1);
    for (LL i = 1; i <= q; i++) {
      cin >> l[0] >> r[0];
      unsigned LL ans = 0;
      for (LL x = 1; x <= n; x++) {
        for (LL y = x + 1; y <= n; y++) {
          LL lca1 = Lca(x, y, 0), lca2 = Lca(x, y, 1);
          if (v[0][lca1].w >= l[0] && v[0][lca1].w <= r[0] && v[1][lca2].w >= l[1] && v[1][lca2].w <= r[1]) {
            ans += (unsigned LL)v[0][lca1].w * v[1][lca2].w;
          }
        }
      }
      w ^= ans;
      if (i <= 10000) {
        cout << ans << '\n';
      }
    }
    cout << w << '\n';
  }
  return 0;
}
