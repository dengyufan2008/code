#include <iostream>
#include <queue>

using namespace std;

const int kMaxN = 21, kV = 100, kReject = 1e6, kMaxFlow = 1e9;
const int kMove[2][2] = {{1, 0}, {0, 1}};
int n, s, t, a[kMaxN][kMaxN];
class Dinic {  // t should be maxinum.
  static const int kMaxE = kMaxN * kMaxN * 70;
  static const int kMaxV = kMaxN * kMaxN * 6;

 public:
  struct E {
    int p, d, w;
  } e[kMaxE << 1];
  struct V {
    int et, nt, d;
  } v[kMaxV];

 private:
  int k, s, t;
  queue<int> q;

  bool Bfs() {
    for (int i = 1; i <= t; i++) {
      v[i].nt = v[i].et, v[i].d = i == s;
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
      if (e[i].w && v[e[i].d].d == v[x].d + 1) {
        int t = Dfs(e[i].d, min(in, e[i].w));
        e[i].w -= t, e[i ^ 1].w += t;
        in -= t, out += t;
      }
    }
    return out;
  }

 public:
  void Clear() { k = 1, fill(&v[1], &v[t] + 1, v[0]), s = t = 0; }
  Dinic() { Clear(); }

  void AddEdge(int x, int y, int w) {
    e[++k] = {v[x].et, y, w}, v[x].et = k;
    e[++k] = {v[y].et, x, 0}, v[y].et = k;
  }

  int Calc(int _s, int _t) {
    int ans = 0;
    for (s = _s, t = _t; Bfs(); ans += Dfs(s, kMaxFlow)) {
    }
    return ans;
  }
} dinic;

int R(int x, int y, int o) {
  return ((x - 1) * n + y) * 6 + o;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  s = n * n * 6 + 1, t = s + 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      dinic.AddEdge(s, R(i, j, 1), kReject);
      dinic.AddEdge(R(i, j, 6), t, kReject);
      for (int x = 1; x <= 5; x++) {
        dinic.AddEdge(R(i, j, x), R(i, j, x + 1), !a[i][j] || a[i][j] == x ? kV : kReject);
      }
      for (int o = 0; o <= 1; o++) {
        int _i = i + kMove[o][0], _j = j + kMove[o][1];
        if (max(_i, _j) <= n) {
          for (int x = 1; x <= 5; x++) {
            dinic.AddEdge(R(i, j, x + 1), R(_i, _j, x), 1);
            dinic.AddEdge(R(_i, _j, x + 1), R(i, j, x), 1);
          }
          for (int d = 2; d <= 4; d++) {
            for (int x = 1; x <= 6 - d; x++) {
              dinic.AddEdge(R(i, j, x + d), R(_i, _j, x), 2);
              dinic.AddEdge(R(_i, _j, x + d), R(i, j, x), 2);
            }
          }
        }
      }
    }
  }
  cout << dinic.Calc(s, t) - n * n * kV << '\n';
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int ans = 0;
      for (int x = 1; x <= 5 && ans; x++) {
        for (int k = dinic.v[R(i, j, x)].et; k; k = dinic.e[k].p) {
          if (dinic.e[k].d == R(i, j, x + 1)) {
            ans = !dinic.e[k].w ? x : 0;
            break;
          }
        }
      }
      cout << ans << " \n"[j == n];
    }
  }
  return 0;
}
