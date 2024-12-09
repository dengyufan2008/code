#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("length.in");
ofstream cout("length.out");

const LL kMaxN = 302, kInf = 1e14;
struct V {
  int f, c, r, s;
  vector<int> e;
} v[kMaxN];
int o, n, m, k, r, a[kMaxN];
LL ans, f[2][kMaxN][kMaxN];

void Init(int f, int x, bool o) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (i != f) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  v[x].f = f, v[x].c = o, v[x].r = ++k, v[x].s = 1;
  if (o && v[x].e.empty()) {
    o = 0, v[x].e.push_back(++m);
  }
  for (int i : v[x].e) {
    Init(x, i, o), v[x].c += v[i].c, v[x].s += v[i].s;
  }
}

bool In(int x, int y) { return v[x].r <= v[y].r && v[x].r + v[x].s > v[y].r; }
void Update(LL &x, LL y) { x = max(x, y); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> n, m = n + 1, k = ans = 0;
    for (int i = 1; i <= m; i++) {
      v[i].e.clear();
    }
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1, x, y; i <= n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    for (r = 1; v[r].e.size() == 1; r++) {
    }
    Init(0, r, 1);
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= m; j++) {
        f[0][i][j] = -kInf;
      }
    }
    for (int i : v[r].e) {
      for (int j : v[r].e) {
        f[0][i][j] = 0;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (i != r) {
        for (int j : v[i].e) {
          f[0][i][j] = 0;
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int k = 1; k <= m; k++) {
          f[i & 1][j][k] = -kInf;
        }
      }
      for (int j = 1; j <= m; j++) {
        for (int k = 1; k <= m; k++) {
          if (j != r && k != r && f[i & 1 ^ 1][j][k] > -kInf) {
            LL w = f[i & 1 ^ 1][j][k] + a[i];
            Update(f[i & 1][j][k], f[i & 1 ^ 1][j][k]);
            if (In(j, k) && i <= v[j].c - v[k].c) {
              if (v[j].f != r) {
                Update(f[i & 1][v[j].f][k], w);
              }
              for (int l : v[v[j].f].e) {
                if (j != l) {
                  Update(f[i & 1][l][k], w);
                }
              }
              for (int l : v[k].e) {
                Update(f[i & 1][j][l], w);
              }
            }
            if (!In(j, k) && i <= n + 1 - v[j].c - v[k].c) {
              for (int l : v[j].e) {
                Update(f[i & 1][l][k], w);
              }
              for (int l : v[k].e) {
                Update(f[i & 1][j][l], w);
              }
            }
          }
        }
      }
    }
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= m; j++) {
        ans = max(ans, f[n & 1][i][j]);
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
