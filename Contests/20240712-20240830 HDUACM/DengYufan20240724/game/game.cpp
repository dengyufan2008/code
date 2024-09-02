#include <fstream>
#include <queue>

using namespace std;

ifstream cin("game.in");
ofstream cout("game.out");

const int kMaxN = 1e5 + 1, kMaxM = 4.8e5 + 1, kInf = 1e9;
struct E {
  int p, d, w;
} e[kMaxM];
struct V {
  int d, et, nt;
} v[kMaxN];
int n, m, a, b, s, t;

void AddEdge(int x, int y, int w) {
  static int k = 1;
  e[++k] = {v[x].et, y, w}, v[x].et = k;
  e[++k] = {v[y].et, x, 0}, v[y].et = k;
}

bool Bfs() {
  static queue<int> q;
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
      int w = Dfs(e[i].d, min(in, e[i].w));
      e[i].w -= w, e[i ^ 1].w += w;
      in -= w, out += w;
    }
  }
  return out;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> a;
  for (int i = 1, x, y; i <= a; i++) {
    cin >> x >> y;
    AddEdge(n + m + i, x, 1);
    AddEdge(n + m + i, n + y, 1);
  }
  cin >> b;
  for (int i = 1, x, y; i <= b; i++) {
    cin >> x >> y;
    AddEdge(x, n + m + a + i, 1);
    AddEdge(n + y, n + m + a + i, 1);
  }
  s = n + m + a + b + 1, t = s + 1;
  for (int i = a; i >= 1; i--) {
    AddEdge(s, n + m + i, 1);
  }
  for (int i = b; i >= 1; i--) {
    AddEdge(n + m + a + i, t, 1);
  }
  for (; Bfs(); Dfs(s, kInf)) {
  }
  Bfs();
  for (int i = v[s].et; i; i = e[i].p) {
    cout << (!e[i].w && !v[e[i].d].d) << '\n';
  }
  return 0;
}
