#include <iostream>
#include <queue>
#define LL long long

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 1e3 + 1, kMaxM = 2e4 + 1;
const LL kInf = 1e18;
struct E {
  int p, d;
  LL w;
} e[kMaxM];
struct V {
  LL d;
  int et, nt;
} v[kMaxN];
int n, m, k, s, t;
LL ans;
queue<int> q;

void AddEdge(int x, int y, LL z, bool b) {
  e[++k] = {v[x].et, y, z}, v[x].et = k;
  e[++k] = {v[y].et, x, b * kInf}, v[y].et = k;
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

LL Dfs(int x, LL in) {
  if (x == t) {
    return in;
  }
  LL out = 0;
  for (int &i = v[x].nt; i && in; in && (i = e[i].p)) {
    if (e[i].w && v[x].d + 1 == v[e[i].d].d) {
      LL f = Dfs(e[i].d, min(e[i].w, in));
      e[i].w -= f, e[i ^ 1].w += f;
      in -= f, out += f;
    }
  }
  return out;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  k = 1, s = n + 2, t = n + 3;
  AddEdge(s, 1, 0, 1), AddEdge(1, t, kInf, 1);
  AddEdge(s, n + 1, kInf, 1), AddEdge(n + 1, t, 0, 1);
  for (int i = 2, x; i <= n; i++) {
    cin >> x;
    AddEdge(s, i, x, 1);
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    AddEdge(i, i + 1, x, 0), AddEdge(i + 1, i, x, 0);
  }
  for (int i = 2, x; i <= n; i++) {
    cin >> x;
    AddEdge(i, t, x, 1);
  }
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    AddEdge(y + 1, x + 1, z, 0);
  }
  for (; Bfs(); ans += Dfs(s, kInf)) {
  }
  cout << ans;
  return 0;
}
