#pragma GCC optimize("O2")
#include <iostream>
#include <queue>

using namespace std;

const int kMaxN = 101, kEdge = 1e4, kReject = 1e8, kInf = 1e9;
const int kMove[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
struct E {
  int p, d, w;
} e[kMaxN * kMaxN * 22];
struct V {
  int d, et, nt;
} v[kMaxN * kMaxN * 3];
int o, n, m, k, s, t, ans;
char c[kMaxN][kMaxN];
queue<int> q;

int Read() {
  int x = 0, c = getchar();
  while (c < 48 || c > 57) {
    c = getchar();
  }
  while (c > 47 && c < 58) {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
  return x;
}

int R(int x, int y, int z) {
  return z * n * m + (x - 1) * m + y;
}

void AddEdge(int x, int y, int w) {
  e[++k] = {v[x].et, y, w}, v[x].et = k;
  e[++k] = {v[y].et, x, 0}, v[y].et = k;
}

bool Bfs() {
  for (int i = 1; i <= t; i++) {
    v[i].d = i == s, v[i].nt = v[i].et;
  }
  for (q.push(s); !q.empty(); q.pop()) {
    for (int i = v[q.front()].et; i; i = e[i].p) {
      if (e[i].w && !v[e[i].d].d) {
        v[e[i].d].d = v[q.front()].d + 1;
        q.push(e[i].d);
      }
    }
  }
  return v[t].d;
}

int Dfs(int x, int in) {
  if (x == t) {
    return in;
  }
  int out = 0;
  for (int &i = v[x].nt; i && in; in && (i = e[i].p)) {
    if (e[i].w && v[x].d + 1 == v[e[i].d].d) {
      int t = Dfs(e[i].d, min(in, e[i].w));
      e[i].w -= t, e[i ^ 1].w += t;
      in -= t, out += t;
    }
  }
  return out;
}

int main() {
  freopen("matrix.in", "r", stdin);
  freopen("matrix.out", "w", stdout);
  ios::sync_with_stdio(0);
  o = Read();
  while (o--) {
    n = Read(), m = Read();
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        c[i][j] = getchar();
        while (c[i][j] != '0' && c[i][j] != '1' && c[i][j] != '?') {
          c[i][j] = getchar();
        }
        if ((i + j & 1) && (c[i][j] != '?')) {
          c[i][j] ^= 1;
        }
      }
    }
    for (int i = 1; i <= t; i++) {
      v[i].et = 0;
    }
    s = n * m * 3 + 1, t = s + 1, k = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        AddEdge(s, R(i, j, 2), c[i][j] != '1' ? kEdge : kReject);
        AddEdge(R(i, j, 2), t, c[i][j] != '0' ? kEdge : kReject);
      }
    }
    for (int i = 1; i < n; i++) {
      for (int j = 1; j < m; j++) {
        AddEdge(R(i, j, 0), R(i, j, 1), 1);
        for (int u = 0; u < 4; u++) {
          int _i = i + kMove[u][0], _j = j + kMove[u][1];
          AddEdge(R(_i, _j, 2), R(i, j, 0), 1);
          AddEdge(R(i, j, 1), R(_i, _j, 2), 1);
        }
      }
    }
    for (ans = 0; Bfs(); ans += Dfs(s, kInf)) {
    }
    cout << (n - 1) * (m - 1) + n * m * kEdge - ans << '\n';
  }
  return 0;
}
