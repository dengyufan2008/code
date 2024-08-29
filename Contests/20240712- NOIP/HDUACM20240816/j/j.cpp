#include <fstream>
#include <vector>
#define LL long long
#define R(x) x + kMaxN

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const LL kMaxN = 4001, kInf = 1e18;
struct V {
  int s, b;
  LL f[kMaxN << 1][2];  // +:out -:in 0:neednt 1:need
  vector<pair<int, int>> e;
} v[kMaxN];
int t, n;
LL m, f[kMaxN << 1][2], _f[kMaxN << 1][2];  // only neednt, 0:no neg 1:exist neg
LL g[kMaxN << 1], _g[kMaxN << 1];           // whatever

void Update(LL &x, LL y) { x = min(x, y); }

void T(int o, int x) {
  for (auto u : v[x].e) {
    if (u.first != o) {
      T(x, u.first);
    }
  }
  v[x].s = 1;
  fill(&v[x].f[R(-n)][0], &v[x].f[R(n)][2], kInf);
  if (v[x].e.empty() || v[x].e.size() == 1 && v[x].e.front().first == o) {
    v[x].f[R(0)][1] = v[x].f[R(-1)][0] = 0, v[x].b && (v[x].f[R(1)][1] = 0);
    return;
  }
  fill(&f[R(-n)][0], &f[R(n)][2], kInf);
  fill(&g[R(-n)], &g[R(n)] + 1, kInf);
  f[R(0)][0] = g[R(0)] = 0, v[x].b && (g[R(1)] = 0);
  for (auto u : v[x].e) {
    int i = u.first, w = u.second;
    if (i != o) {
      for (int j = -v[i].s; j <= v[i].s; j++) {
        v[i].f[R(j)][1] = min(v[i].f[R(j)][0], v[i].f[R(j)][1] + w);
      }
      for (int j = -v[i].s; j < 0; j++) {
        v[i].f[R(j)][0] -= j * m;
      }
      for (int j = -v[x].s; j <= 0; j++) {
        _f[R(j)][0] = min(f[R(j)][0] + v[i].f[R(0)][0], kInf);
        _f[R(j)][1] = min(f[R(j)][1] + v[i].f[R(0)][0], kInf);
      }
      for (int j = -v[x].s; j <= 0; j++) {
        for (int k = -v[i].s; k < 0; k++) {
          Update(_f[R(j + k)][1], min(f[R(j)][0], f[R(j)][1]) + v[i].f[R(k)][0]);
        }
      }
      for (int j = -v[x].s; j <= v[x].s; j++) {
        for (int k = -v[i].s; k <= v[i].s; k++) {
          Update(_g[R(j + k)], g[R(j)] + v[i].f[R(k)][1] + abs(k) * m);
        }
      }
      v[x].s += v[i].s;
      for (int j = -v[x].s; j <= 0; j++) {
        f[R(j)][0] = _f[R(j)][0], _f[R(j)][0] = kInf;
        f[R(j)][1] = _f[R(j)][1], _f[R(j)][1] = kInf;
      }
      for (int j = -v[x].s; j <= v[x].s; j++) {
        g[R(j)] = _g[R(j)], _g[R(j)] = kInf;
      }
    }
  }
  for (int i = -v[x].s; i <= v[x].s; i++) {
    v[x].f[R(i)][0] = f[R(i)][1];
    v[x].f[R(i)][1] = g[R(i)];
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fill(&_f[1][0], &_f[kMaxN << 1][0], kInf);
  fill(&_g[1], &_g[kMaxN << 1], kInf);
  cin >> t;
  while (t--) {
    for (int i = 1; i <= n; i++) {
      v[i].e.clear();
    }
    cin >> n >> m, m *= 2;
    for (int i = 1; i <= n; i++) {
      cin >> v[i].b;
    }
    for (int i = 1, x, y, z; i < n; i++) {
      cin >> x >> y >> z, z *= 2;
      v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
    }
    T(0, 1);
    cout << min(v[1].f[R(0)][0], v[1].f[R(0)][1]) << '\n';
  }
  return 0;
}
