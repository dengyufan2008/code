#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 31;
int o, n, m, k;
bool b[kMaxN][kMaxN];

class EK {
  static const LL kMaxV = 2001, kMaxE = 9001, kInf = 1e18;
  struct E {
    int p, d;
    LL w, l;
  } e[kMaxE << 1];
  struct V {
    int et, nt;
    LL d;
    bool b;
  } v[kMaxV];
  int n, s, t, o;

  bool Spfa() {
    static queue<int> q;
    for (int i = 1; i <= n; i++) {
      v[i].d = i == s ? 0 : kInf;
      v[i].b = i == s;
    }
    for (q.push(s); !q.empty(); q.pop()) {
      int x = q.front();
      v[x].b = 0;
      for (int i = v[x].et; i; i = e[i].p) {
        int y = e[i].d;
        if (e[i].w && v[y].d > v[x].d + e[i].l) {
          v[y].d = v[x].d + e[i].l;
          if (!v[y].b) {
            v[y].b = 1, q.push(y);
          }
        }
      }
    }
    return v[t].d < kInf;
  }

  LL Dfs(int x, LL in) {
    if (v[x].b) {
      return 0;
    } else if (x == t) {
      return in;
    }
    LL out = 0;
    v[x].b = 1;
    for (int &i = v[x].nt; i && in; in && (i = e[i].p)) {
      int y = e[i].d;
      if (e[i].w && v[x].d + e[i].l == v[y].d) {
        LL t = Dfs(y, min(e[i].w, in));
        e[i].w -= t, e[i ^ 1].w += t;
        in -= t, out += t;
      }
    }
    v[x].b = 0;
    return out;
  }

 public:
  void Init(int _n, int _s, int _t) {
    n = _n, s = _s, t = _t, o = 1;
    for (int i = 1; i <= n; i++) {
      v[i].et = 0;
    }
  }

  void AddEdge(int x, int y, LL w, LL l) {
    e[++o] = {v[x].et, y, w, l}, v[x].et = o;
    e[++o] = {v[y].et, x, 0, -l}, v[y].et = o;
  }

  pair<LL, LL> Flow() {
    pair<LL, LL> ans;
    for (; Spfa();) {
      for (int i = 1; i <= n; i++) {
        v[i].nt = v[i].et, v[i].b = 0;
      }
      LL w = Dfs(s, kInf);
      ans.first += w, ans.second += w * v[t].d;
    }
    return ans;
  }
} ek;

int R(int x, int y, bool o) {
  return (x - 1) * m + y + o * n * m;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> n >> m;
    int s = n * m * 2 + 1, t = s + 1;
    ek.Init(t, s, t);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (i + j & 1) {
          ek.AddEdge(s, R(i, j, 0), 1, 0);
          ek.AddEdge(R(i, j, 1), t, 1, 0);
        } else {
          ek.AddEdge(s, R(i, j, 1), 1, 0);
          ek.AddEdge(R(i, j, 0), t, 1, 0);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1, x; j < m; j++) {
        cin >> x;
        if (i + j & 1) {
          ek.AddEdge(R(i, j, 0), R(i, j + 1, 0), 1, -x);
        } else {
          ek.AddEdge(R(i, j + 1, 0), R(i, j, 0), 1, -x);
        }
      }
    }
    for (int i = 1; i < n; i++) {
      for (int j = 1, x; j <= m; j++) {
        cin >> x;
        if (i + j & 1) {
          ek.AddEdge(R(i + 1, j, 1), R(i, j, 1), 1, -x);
        } else {
          ek.AddEdge(R(i, j, 1), R(i + 1, j, 1), 1, -x);
        }
      }
    }
    cin >> k;
    for (int i = 1, x, y; i <= k; i++) {
      cin >> x >> y, b[x][y] = 1;
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (b[i][j]) {
          b[i][j] = 0;
        } else if (i + j & 1) {
          ek.AddEdge(R(i, j, 0), R(i, j, 1), 1, 0);
        } else {
          ek.AddEdge(R(i, j, 1), R(i, j, 0), 1, 0);
        }
      }
    }
    auto ans = ek.Flow();
    if (ans.first == n * m) {
      cout << -ans.second << '\n';
    } else {
      cout << "Impossible\n";
    }
  }
  return 0;
}
