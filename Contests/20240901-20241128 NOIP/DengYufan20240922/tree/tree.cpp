#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("tree.in");
ofstream cout("tree.out");

const LL kMaxN = 3001, kInf = 1e18;
struct E {
  int x, l, w;
};
struct V {
  LL d[kMaxN], f[kMaxN];
  vector<E> e;
} v[kMaxN];
int t, n, m;
LL ans, g[kMaxN];

void CalcD(int f, int x, int s) {
  for (E i : v[x].e) {
    if (i.x != f) {
      v[s].d[i.x] = v[s].d[x] + i.l;
      CalcD(x, i.x, s);
    }
  }
}

void CalcF(int f, int x) {
  for (int i = 1; i <= n; i++) {
    if (v[x].d[i] <= m) {
      v[x].f[i] = 0;
    }
  }
  LL mx;
  for (E i : v[x].e) {
    if (i.x != f) {
      CalcF(x, i.x), mx = -kInf;
      for (int j = 1; j <= n; j++) {
        g[j] = v[x].f[j] + v[i.x].f[j] + i.w;
        mx = max(mx, v[i.x].f[j]);
      }
      for (int j = 1; j <= n; j++) {
        v[x].f[j] = max(max(g[j], v[x].f[j] + mx), -kInf);
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fill(&v[0].f[0], &v[0].f[kMaxN], -kInf);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    ans = -kInf, fill(&v[1], &v[n] + 1, v[0]);
    for (int i = 1, x, y, l, w; i < n; i++) {
      cin >> x >> y >> l >> w;
      v[x].e.push_back({y, l, w});
      v[y].e.push_back({x, l, w});
    }
    for (int i = 1; i <= n; i++) {
      CalcD(0, i, i);
    }
    CalcF(0, 1);
    for (int i = 1; i <= n; i++) {
      ans = max(ans, v[1].f[i]);
    }
    cout << ans << '\n';
  }
  return 0;
}
