#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const LL kMaxN = 200, kMaxM = 10, kMod = 1e9 + 7, kInf = 1e18;
struct V {
  LL f, g;
} f[1 << kMaxM][kMaxN], g[1 << kMaxM][kMaxN][2];
int n, m, k, a[kMaxN];
vector<int> c[kMaxN];
vector<pair<int, int>> e[kMaxN];

void Update(V &x, V y) {
  if (x.f > y.f) {
    x = y;
  } else if (x.f == y.f) {
    x.g = (x.g + y.g) % kMod;
  }
}

V Merge(V x, V y) {
  return {x.f + y.f, x.g * y.g % kMod};
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k;
  for (int i = 0; i < k; i++) {
    c[i].resize(1);
  }
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    c[--a[i]].push_back(i);
  }
  for (int i = 1, x, y, w; i <= m; i++) {
    cin >> x >> y >> w;
    x--, y--, e[x].push_back({y, w}), e[y].push_back({x, w});
  }
  for (int s = 1; s < (1 << k); s++) {
    for (int i = 0; i < k; i++) {
      if (s >> i & 1) {
        g[0][0][0] = {0, 1}, fill(&g[0][0][1], &g[1 << kMaxM][0][0], (V){kInf, 0});
        for (int j = 1; j < c[i].size(); j++) {
          ;
        }
        for (int j = 1; j < c[i].size(); j++) {  // f[i][c[i][j]]
          Update(f[i][c[i][j]], Merge(g[]))
        }
      }
    }
  }
  return 0;
}
