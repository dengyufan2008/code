#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("pois.in");
ofstream cout("pois.out");

const LL kMaxN = 301, kInf = 2e6;
struct E {
  int p, d;
  LL w;
} e[kMaxN * kMaxN * 3];
struct V {
  int d, et, nt;
} v[kMaxN * 3];
int n, s, t;
LL ans;
queue<int> q;

void AddEdge(int x, int y, LL w) {
  static int k = 1;
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

LL Dfs(int x, LL in) {
  if (x == t) {
    return in;
  }
  LL out = 0;
  for (int &i = v[x].nt; i && in; in && (i = e[i].p)) {
    if (e[i].w && v[x].d + 1 == v[e[i].d].d) {
      LL t = Dfs(e[i].d, min(in, e[i].w));
      e[i].w -= t, e[i ^ 1].w += t;
      in -= t, out += t;
    }
  }
  return out;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  s = n * 2 + 1, t = n * 2 + 2;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    AddEdge(i + n, t, kInf);
    for (int j = 1, y; j <= x; j++) {
      cin >> y;
      AddEdge(i, y + n, kInf);
    }
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x, ans += x;
    AddEdge(s, i, kInf - x);
  }
  for (; Bfs(); ans += Dfs(s, kInf * kInf)) {
  }
  cout << ans - n * kInf << '\n';
  return 0;
}
