#include <iostream>
#include <queue>

using namespace std;

const int kMaxN = 21, kMaxM = 6, kInf = 1e9;
const int kMove[2][2] = {{1, 0}, {0, 1}};
int n, a[kMaxN][kMaxN];
class H {
  struct E {
    int p, d, w;
  } e[kMaxN * 2];
  struct V {
    int d, et, nt;
  } v[kMaxN];
  int k, s, t;
  queue<int> q;

  bool Bfs() {
    for (int i = 1; i <= t; i++) {
      v[i].d = i == s, v[i].nt = v[i].et;
    }
    for (q.push(s); !q.empty(); q.pop()) {
      for (int i = v[q.front()].et; i; i = e[i].p) {
        if (e[i].w && !v[e[i].d].d) {
          v[e[i].d].d = v[q.front()].d + 1, q.push(e[i].d);
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

 public:
  H() : k(1) {}

  void AddEdge(int x, int y, int w) {
    e[++k] = {v[x].et, y, w}, v[x].et = k;
    e[++k] = {v[y].et, x, 0}, v[y].et = k;
  }

  int Flow() {
    for (int i = 1; v[i].et; i++) {
      s = i - 1, t = i;
    }
    int ans = 0;
    for (; Bfs(); ans += Dfs(s, kInf)) {
    }
    return ans;
  }
} h;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int o : {0, 1}) {
        int _i = i + kMove[o][0], _j = j + kMove[o][1];
        if (max(_i, _j) <= n) {
          ;
        }
      }
    }
  }
  return 0;
}
