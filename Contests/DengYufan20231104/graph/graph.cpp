#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("graph.in");
ofstream cout("graph.out");

const int kMaxN = 3001, kInf = 1e9;
struct Flow {
  struct E {
    int p, d, w, l;
  } e[kMaxN * 16];
  struct V {
    int et, p;
    LL d;
    bool b;
  } v[kMaxN * 5];
  int m = 1, s, t;

  void AddEdge(int x, int y, int w = 1, int l = 0) {
    e[++m] = {v[x].et, y, w, -l}, v[x].et = m;
    e[++m] = {v[y].et, x, 0, l}, v[y].et = m;
  }

  bool Spfa() {
    queue<int> q;
    for (int i = 1; i <= t; i++) {
      v[i].d = (i != s) * kInf, v[i].b = i == s;
    }
    for (q.push(s); !q.empty(); q.pop()) {
      int x = q.front();
      v[x].b = 0;
      for (int i = v[x].et; i; i = e[i].p) {
        if (e[i].w && v[e[i].d].d > v[x].d + e[i].l) {
          v[e[i].d].d = v[x].d + e[i].l, v[e[i].d].p = i;
          if (!v[e[i].d].b) {
            v[e[i].d].b = 1, q.push(e[i].d);
          }
        }
      }
    }
    return v[t].d < kInf;
  }

  LL Calc(int _s, int _t, int k) {
    LL ans = 0;
    s = _s, t = _t;
    for (; k-- && Spfa();) {
      for (int i = t; i != s; i = e[v[i].p ^ 1].d) {
        e[v[i].p].w--, e[v[i].p ^ 1].w++;
      }
      ans -= v[t].d;
    }
    return ans;
  }
} flow;
int n, k, x, y, z, in, out, sub, mul, mod, s, t, a[kMaxN];

int Find(int x, bool Cmp(int s, int t)) {
  for (int i = x + 1; i <= n; i++) {
    if (Cmp(x, i)) {
      return i;
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k >> x >> y >> z;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  in = 0, out = n, sub = out + n, mul = sub + n, mod = mul + n, s = mod + n + 1, t = s + 1;
  for (int i = 1, j; i <= n; i++) {
    flow.AddEdge(s, i + in);
    flow.AddEdge(i + sub, i + in);
    flow.AddEdge(i + mul, i + in);
    flow.AddEdge(i + mod, i + in);
    flow.AddEdge(i + in, i + out, 1, 1);
    flow.AddEdge(i + out, t);
    j = Find(i, [](int s, int t) { return a[s] - a[t] == x; });
    if (j) {
      flow.AddEdge(i + out, j + sub);
    }
    j = Find(i, [](int s, int t) { return a[t] - a[s] == x; });
    if (j) {
      flow.AddEdge(i + out, j + sub);
    }
    j = Find(i, [](int s, int t) { return y && (1LL * a[t] * y == a[s] || 1LL * a[s] * y == a[t]); });
    if (j) {
      flow.AddEdge(i + out, j + mul);
    }
    j = Find(i, [](int s, int t) { return !((a[s] - a[t]) % z); });
    if (j) {
      flow.AddEdge(i + out, j + mod);
    }
    j = Find(i, [](int s, int t) { return a[s] == a[t]; });
    if (j) {
      flow.AddEdge(i + sub, j + sub);
      flow.AddEdge(i + mul, j + mul);
    }
  }
  cout << flow.Calc(s, t, k);
  return 0;
}
