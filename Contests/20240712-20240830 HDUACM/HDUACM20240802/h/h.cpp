#include <fstream>
#include <queue>

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const int kMaxN = 1001, kMaxV = 3001, kMaxE = 16001, kInf = 30000;
struct A {
  int x, y, z;
};
struct E {
  int p, d, w;
} e[kMaxE];
struct V {
  int d, et, nt;
} v[kMaxV];
int o, n, m, k, s, t, ans;
bool b[kMaxN];
vector<A> l[2];
queue<int> q;

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
    k = 1, ans = 0, l[0].clear(), l[1].clear();
    for (int i = 1; i <= n; i++) {
      b[i] = 0;
    }
    for (int i = 1; i <= t; i++) {
      v[i].et = 0;
    }
    cin >> n >> m;
    for (int i = 1, x; i <= m; i++) {
      cin >> x, b[x] = 1;
    }
    for (int i = 1, x, y, z; i < n; i++) {
      cin >> x >> y >> z;
      if (b[x] && b[y]) {
        ans += z, l[0].push_back({x, y, z});
      }
    }
    for (int i = 1, x, y, z; i < n; i++) {
      cin >> x >> y >> z;
      if (b[x] && b[y]) {
        ans += z, l[1].push_back({x, y, z});
      }
    }
    s = n + l[0].size() + l[1].size() + 1, t = s + 1;
    for (int i = 1; i <= n; i++) {
      if (b[i]) {
        AddEdge(s, i, kInf), AddEdge(i, t, kInf);
      }
    }
    for (int i = 0; i < l[0].size(); i++) {
      AddEdge(l[0][i].x, n + i + 1, kInf);
      AddEdge(l[0][i].y, n + i + 1, kInf);
      AddEdge(n + i + 1, t, l[0][i].z);
    }
    for (int i = 0; i < l[1].size(); i++) {
      AddEdge(n + l[0].size() + i + 1, l[1][i].x, kInf);
      AddEdge(n + l[0].size() + i + 1, l[1][i].y, kInf);
      AddEdge(s, n + l[0].size() + i + 1, l[1][i].z);
    }
    for (ans += m * kInf; Bfs(); ans -= Dfs(s, kInf * kInf)) {
    }
    cout << ans << '\n';
  }
  return 0;
}
