#include <iostream>
#include <queue>

using namespace std;

const int kMaxN = 41, kMaxV = 6403, kMaxE = 17601, kInf = 1e9;
int o, n, m, a, b, c, s, t, k;
int br[kMaxN][kMaxN], bc[kMaxN][kMaxN], wr[kMaxN][kMaxN], wc[kMaxN][kMaxN];
char ch;
class Dinic {  // t should be maxinum.
  struct E {
    int p, d, w;
  } e[kMaxE << 1];
  struct V {
    int et, nt, d;
  } v[kMaxV];
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
    for (s = _s, t = _t; Bfs(); ans += Dfs(s, kInf)) {
    }
    return ans;
  }
} dinic;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> n >> m >> a >> b >> c;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        br[i][j] = ++k, bc[i][j] = ++k;
        wr[i][j] = ++k, wc[i][j] = ++k;
      }
    }
    s = ++k, t = ++k, k = 0, dinic.Clear();
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cin >> ch;
        dinic.AddEdge(br[i][j], t, a);
        dinic.AddEdge(s, bc[i][j], a);
        dinic.AddEdge(s, wr[i][j], a);
        dinic.AddEdge(wc[i][j], t, a);
        dinic.AddEdge(i < n ? bc[i + 1][j] : s, bc[i][j], b);
        dinic.AddEdge(wc[i][j], i < n ? wc[i + 1][j] : t, b);
        dinic.AddEdge(br[i][j], j < m ? br[i][j + 1] : t, b);
        dinic.AddEdge(j < m ? wr[i][j + 1] : s, wr[i][j], b);
        if (ch == '1') {
          dinic.AddEdge(bc[i][j], br[i][j], c);
          dinic.AddEdge(s, wr[i][j], kInf);
          dinic.AddEdge(wc[i][j], t, kInf);
        } else {
          dinic.AddEdge(br[i][j], wc[i][j], c);
          dinic.AddEdge(wr[i][j], bc[i][j], c);
          dinic.AddEdge(br[i][j], bc[i][j], kInf);
        }
      }
    }
    cout << dinic.Calc(s, t) << '\n';
  }
  return 0;
}
