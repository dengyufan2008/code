#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 501, kInf = 1e9;
struct V {
  int p, h, d;
  bool b;
} v[kMaxN * 2 + 1];
int o, n, k, s, t, ans, a[kMaxN];
int d[kMaxN * 2 + 1][kMaxN * 2 + 1];
bool e[kMaxN * 2 + 1][kMaxN * 2 + 1];

void AddEdge(int x, int y, int w, int l) {
  e[x][y] = 1, d[x][y] = l, d[y][x] = -l;
}

void Dij() {
  for (int i = 1; i <= t; i++) {
    v[i].d = i == s ? 0 : kInf, v[i].b = 0;
  }
  for (int i = 1; i <= t; i++) {
    int x = 0;
    for (int j = 1; j <= t; j++) {
      if (!v[j].b && (!x || v[j].d < v[x].d)) {
        x = j;
      }
    }
    v[x].b = 1;
    for (int j = 1; j <= t; j++) {
      if (e[x][j]) {
        int l = v[x].d + d[x][j] + v[x].h - v[j].h;
        if (v[j].d > l) {
          v[j].d = l, v[j].p = x;
        }
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    k = 1, ans = 0;
    for (int i = 1; i <= t; i++) {
      for (int j = 1; j <= t; j++) {
        e[i][j] = 0;
      }
    }
    cin >> n, s = n * 2 + 1, t = s + 1;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        if (a[i] > a[j]) {
          AddEdge(i * 2, j * 2 - 1, 1, 0);
        }
      }
    }
    for (int i = 1, x; i <= n; i++) {
      cin >> x, ans += x;
      v[i * 2 - 1].h = v[i * 2 - 2].h;
      v[i * 2].h = v[i * 2 - 1].h - x;
      AddEdge(s, i * 2 - 1, 1, 0);
      AddEdge(i * 2, t, 1, 0);
      AddEdge(i * 2 - 1, i * 2, 1, -x);
    }
    v[s].h = 0, v[t].h = v[n * 2].h;
    for (int i = 1; i <= n; i++) {
      if (ans) {
        Dij();
        for (int j = 1; j <= t; j++) {
          v[j].h += v[j].d;
        }
        for (int j = t; j != s; j = v[j].p) {
          e[v[j].p][j] = 0, e[j][v[j].p] = 1;
        }
        ans += v[t].h;
      }
      cout << ans << " \n"[i == n];
    }
  }
  return 0;
}
