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
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cin >> c[i][j];
        if ((i + j & 1) && (c[i][j] != '?')) {
          c[i][j] ^= 21;
        }
      }
    }
    for (int i = 1; i <= t; i++) {
      v[i].et = 0;
    }
    ans = 0, s = n * m * 3 + 1, t = s + 1, k = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (c[i][j] == 'W') {
          ans += kEdge;
          AddEdge(R(i, j, 2), t, kReject);
        } else if (c[i][j] == 'B') {
          ans += kEdge;
          AddEdge(s, R(i, j, 2), kReject);
        } else {
          AddEdge(R(i, j, 2), t, c[i][j] != 'W' ? kEdge : kReject);
          AddEdge(s, R(i, j, 2), c[i][j] != 'B' ? kEdge : kReject);
        }
      }
    }
    for (int i = 1; i < n; i++) {
      for (int j = 1; j < m; j++) {
        bool w = 1, b = 1;
        for (int u = 0; u < 4; u++) {
          int _i = i + kMove[u][0], _j = j + kMove[u][1];
          if (c[_i][_j] == 'B') {
            w = 0;
          } else if (c[_i][_j] == 'W') {
            b = 0;
          }
        }
        if (w || b) {
          AddEdge(R(i, j, 0), R(i, j, 1), 1);
          for (int u = 0; u < 4; u++) {
            int _i = i + kMove[u][0], _j = j + kMove[u][1];
            AddEdge(R(_i, _j, 2), R(i, j, 0), 1);
            AddEdge(R(i, j, 1), R(_i, _j, 2), 1);
          }
        } else {
          ans++;
        }
      }
    }
    for (; Bfs(); ans += Dfs(s, kInf)) {
    }
    cout << (n - 1) * (m - 1) + n * m * kEdge - ans << '\n';
    for (int i = 1; i <= t; i++) {
      v[i].d = i == s;
    }
    for (q.push(s); !q.empty(); q.pop()) {
      for (int i = v[q.front()].et; i; i = e[i].p) {
        if (e[i].w && !v[e[i].d].d) {
          v[e[i].d].d = 1;
          q.push(e[i].d);
        }
      }
    }
    for (int i = 2; i < k; i += 2) {
      if (v[e[i].d].d ^ v[e[i ^ 1].d].d ^ 1) {
        if (e[i ^ 1].d == s) {
          int x = (e[i].d - n * m * 2 - 1) / m + 1;
          int y = (e[i].d - n * m * 2 - 1) % m + 1;
          for (int u = 0; u < 4; u++) {
            int _x = x + kMove[u][0], _y = y + kMove[u][1];
            if (_x <= n && _y <= m) {
              c[_x][_y] = 'B';
            }
          }
        } else if (e[i].d == t) {
          int x = (e[i ^ 1].d - n * m * 2 - 1) / m + 1;
          int y = (e[i ^ 1].d - n * m * 2 - 1) % m + 1;
          for (int u = 0; u < 4; u++) {
            int _x = x + kMove[u][0], _y = y + kMove[u][1];
            if (_x <= n && _y <= m) {
              c[_x][_y] = 'W';
            }
          }
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        c[i][j] == '?' && (c[i][j] = 'W');
        i + j & 1 && (c[i][j] ^= 21);
        cout << c[i][j];
      }
      cout << '\n';
    }
  }
  return 0;
}
