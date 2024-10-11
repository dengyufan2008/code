#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

const int kMaxN = 2001;
struct V {
  int s;
  LL f[kMaxN], g[kMaxN], h[kMaxN];  // f:还没选 g:选了链 h:选了
  vector<pair<int, int>> e;
} v[kMaxN];
int n, m;

void Update(LL &x, LL y) { x = max(x, y); }

void T(int f, int x) {
  v[x].s = 1;
  for (auto o : v[x].e) {
    int y = o.first, w = o.second;
    if (y != f) {
      T(x, y);
      for (int i = v[x].s; i >= 1; i--) {
        LL h = v[x].h[i];
        for (int j = 1; j <= v[y].s; j++) {
          Update(v[x].h[i + j], h + v[y].h[j] + w);
          Update(v[x].h[i + j - 1], h + v[y].f[j]);
          Update(v[x].h[i + j - 1], v[x].f[i] + v[y].h[j]);
          Update(v[x].h[i + j - 1], v[x].g[i] + v[y].g[j] + w);
        }
      }
      for (int i = v[x].s; i >= 1; i--) {
        LL g = v[x].g[i];
        for (int j = 1; j <= v[y].s; j++) {
          Update(v[x].g[i + j], g + v[y].h[j] + w);
          Update(v[x].g[i + j - 1], g + v[y].f[j]);
          Update(v[x].g[i + j - 1], v[x].f[i] + v[y].g[j] + w);
        }
      }
      for (int i = v[x].s; i >= 1; i--) {
        LL f = v[x].f[i];
        for (int j = 1; j <= v[y].s; j++) {
          Update(v[x].f[i + j], f + v[y].h[j] + w);
          Update(v[x].f[i + j - 1], f + v[y].f[j]);
        }
      }
      v[x].s += v[y].s;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  T(0, 1);
  for (int i = 1; i <= m + 1; i++) {
    cout << v[1].h[min(i, n)] << " \n"[i == m + 1];
  }
  return 0;
}
