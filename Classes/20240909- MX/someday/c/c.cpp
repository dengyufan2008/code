// #define LOCAL
// #define DEBUG

#include <algorithm>
#include <chrono>
#include <random>
#ifdef LOCAL
#include <fstream>
#else
#include <iostream>
#endif

using namespace std;

#ifdef LOCAL
ifstream cin("c.in");
ofstream cout("c.out");
#endif

const int kMaxN = 7.5e4 + 1, kMaxM = 317, kInf = 1e9;
int n, x, y;
#ifdef LOCAL
mt19937 Rand(114514);
#else
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());
#endif

namespace Interactor {
const int kMaxL = 17;
struct V {
  int d, s, f[kMaxL];
  vector<int> e;
} v[kMaxN];
int r1, r2;

void T(int f, int x) {
  int mx = 0;
  v[x].d = v[f].d + 1, v[x].s = 1, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i), v[x].s += v[i].s;
      mx = max(mx, v[i].s);
    }
  }
  if (max(mx, n - v[x].s) * 2 <= n) {
    r1 ? r2 = x : r1 = x;
  }
}

void Init() {
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, 1);
}

int Lca(int x, int y) {
  v[x].d < v[y].d ? swap(x, y) : void();
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = v[x].f[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? x : v[x].f[0];
}

int Ask(int x, int y) {
  if (x >= 1 && x <= n && y >= 1 && y <= n) {
    return v[x].d + v[y].d - v[Lca(x, y)].d * 2;
  } else {
    cout << "Invalid Query!\n";
    exit(0);
  }
}

void Ans(int x) {
  if (x == r1 || x == r2) {
    cout << "Accepted.\n";
  } else {
    cout << "Wrong Answer.\n";
  }
#ifdef DEBUG
  if (r2) {
    cout << "Answer: " << r1 << ' ' << r2 << ".\n";
  } else {
    cout << "Answer: " << r1 << ".\n";
  }
  cout << "Output: " << x << ".\n";
#endif
  exit(0);
}
}  // namespace Interactor

int Ask(int x, int y) {
#ifdef LOCAL
  return Interactor::Ask(x, y);
#else
  static int ans;
  cout << "? " << x << ' ' << y << '\n';
  cout.flush(), cin >> ans;
  return ans;
#endif
}

void Ans(int x) {
#ifdef LOCAL
  Interactor::Ans(x);
#else
  cout << "! " << x << '\n', cout.flush();
#endif
}

namespace FindChain {
int m, r, l[kMaxM], dis[kMaxM << 1][kMaxM << 1], f[kMaxM << 1], s[kMaxN << 1];
bool b[kMaxM << 1][kMaxM << 1];

void CalcDis() {
  static int d[kMaxN];
  for (int i = 1; i <= n; i++) {
    d[i] = i;
  }
  shuffle(d + 1, d + n + 1, Rand);
  for (int i = 1; i <= m; i++) {
    l[i] = d[i % n + 1];
  }
  for (int i = 1; i <= m; i++) {
    dis[i][i] = 0;
    for (int j = i + 1; j <= m; j++) {
      dis[i][j] = dis[j][i] = Ask(l[i], l[j]);
    }
  }
}

bool In(int o, int x, int y) {
  return dis[x][o] + dis[o][y] == dis[x][y];
}

void CalcF() {
  for (int i = 2; i <= m; i++) {
    for (int j = 1; j <= m; j++) {
      if (i != j && In(j, 1, i)) {
        if (!f[i] || dis[1][j] > dis[1][f[i]]) {
          f[i] = j;
        }
      }
    }
  }
  for (int i = 2; i <= m; i++) {
    b[f[i]][i] = 1;
  }
}

void Build(int x) {
  bool o = 1;
  while (o) {
    o = 0;
    for (int i = 1; i <= m && !o; i++) {
      for (int j = i + 1; j <= m && !o; j++) {
        if (b[x][i] && b[x][j] && !In(x, i, j)) {
          o = 1;
          if (In(i, x, j)) {
            f[j] = i, b[x][j] = 0, b[i][j] = 1;
          } else if (In(j, x, i)) {
            f[i] = j, b[x][i] = 0, b[j][i] = 1;
          } else {
            m++, f[i] = f[j] = m, f[m] = x;
            b[x][i] = b[x][j] = 0, b[x][m] = b[m][i] = b[m][j] = 1;
            dis[x][m] = dis[m][x] = dis[x][i] + dis[x][j] - dis[i][j] >> 1;
            dis[i][m] = dis[m][i] = dis[x][i] - dis[x][m];
            dis[j][m] = dis[m][j] = dis[x][j] - dis[x][m];
            for (int k = 1; k < m; k++) {
              if (i != k && j != k && b[x][k]) {
                if (!In(x, i, k) && (dis[x][i] + dis[x][k] - dis[i][k] >> 1 >= dis[x][m])) {
                  f[k] = m, b[x][k] = 0, b[m][k] = 1;
                  dis[k][m] = dis[m][k] = dis[x][k] - dis[x][m];
                } else {
                  dis[k][m] = dis[m][k] = dis[i][k] - dis[i][m];
                }
              }
            }
          }
        }
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    if (b[x][i]) {
      Build(i);
    }
  }
}

void CalcR(int f, int x) {
  int mx = 0;
  s[x] = x <= min(n, kMaxM - 1);
  for (int i = 1; i <= m; i++) {
    if (i != f && b[x][i]) {
      CalcR(x, i), s[x] += s[i];
      mx = max(mx, s[i]);
    }
  }
  if (!r && max(mx, m - s[x]) * 2 <= m) {
    r = x;
  }
}

void FillB() {
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= m; j++) {
      if (b[i][j]) {
        b[j][i] = 1;
      }
    }
  }
}

int CalcChain(int f, int x) {
  int mx = 0;
  for (int i = 1; i <= m; i++) {
    if (i != f && b[x][i]) {
      if (!mx || s[i] > s[mx]) {
        mx = i;
      }
    }
  }
  return mx ? CalcChain(x, mx) : x;
}

void CalcChain() {
  int mx = 0, mx2 = 0;
  for (int i = 1; i <= m; i++) {
    if (b[r][i]) {
      if (!mx || s[i] > s[mx]) {
        mx2 = mx, mx = i;
      } else if (!mx2 || s[i] > s[mx2]) {
        mx2 = i;
      }
    }
  }
  x = CalcChain(r, mx), y = CalcChain(r, mx2);
  x = l[x], y = l[y];
}

void main() {
  m = min(n, kMaxM - 1), CalcDis(), CalcF();
  Build(1), FillB(), CalcR(0, 1), CalcR(0, r), CalcChain();
}
}  // namespace FindChain

namespace FindAns {
int dis, dis1[kMaxN], dis2[kMaxN], l[kMaxN], c[kMaxN];

void main() {
  for (int i = 1; i <= n; i++) {
    dis1[i] = Ask(i, x), dis2[i] = Ask(i, y), c[i - 1] = 0;
  }
  dis = dis1[y];
  for (int i = 1; i <= n; i++) {
    int o = dis1[i] - dis2[i] + dis >> 1;
    c[o]++;
    if (dis1[i] + dis2[i] == dis) {
      l[o] = i;
    }
  }
  for (int i = 0, s = 0; i <= dis; i++) {
    s += c[i];
    if (s * 2 > n) {
      return Ans(l[i]);
    }
  }
}
}  // namespace FindAns

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
#ifdef LOCAL
  Interactor::Init();
#else
  cin >> n;
#endif
  FindChain::main(), FindAns::main();
  return 0;
}
