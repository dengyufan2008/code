#include <iostream>
#include <queue>

using namespace std;

const int kMaxN = 101;
struct V1 {
  int r;
  bool b[kMaxN];
  vector<int> e;
} v1[kMaxN];
struct V2 {
  int f, r;
  vector<int> e;
} v2[kMaxN];
int t, n, m;
class H {
  struct E {
    int p, d, w;
  } e[kMaxN * kMaxN * 2];
  struct V {
    int et, nt, d;
  } v[kMaxN * 2];
  int n, m, s, t, k;
  queue<int> q;

  void AddEdge1(int x, int y) {
    e[++k] = {v[x].et, y, 1}, v[x].et = k;
    e[++k] = {v[y].et, x, 0}, v[y].et = k;
  }

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
      if (v[x].d + 1 == v[e[i].d].d) {
        int t = Dfs(e[i].d, min(in, e[i].w));
        e[i].w -= t, e[i ^ 1].w += t;
        in -= t, out += t;
      }
    }
    return out;
  }

 public:
  void AddEdge(int x, int y) { AddEdge1(x, y + n); }

  void Init(int _n, int _m) {
    k = 1, n = _n, m = _m;
    s = n + m + 1, t = s + 1;
    for (int i = 1; i <= t; i++) {
      v[i].et = 0;
    }
    for (int i = 1; i <= n; i++) {
      AddEdge1(s, i);
    }
    for (int i = 1; i <= m; i++) {
      AddEdge1(i + n, t);
    }
  }

  int Flow() {
    int ans = 0;
    for (; Bfs(); ans += Dfs(s, m)) {
    }
    return ans;
  }
} h;

void S(int f, int x) {
  v2[x].f = f;
  for (int i : v2[x].e) {
    if (i != f) {
      S(x, i);
    }
  }
}

bool ReT(int f, int x, int k) {
  for (int i = 1; i <= m; i++) {
    if (v1[x].b[i] != k) {
      int _n = 0, _m = 0;
      for (int j : v1[x].e) {
        if (j != f) {
          v1[j].r = ++_n;
        }
      }
      for (int j : v2[i].e) {
        if (j != v2[i].f) {
          v2[j].r = ++_m;
        }
      }
      if (_n >= _m && _m) {
        h.Init(_n, _m);
        for (int j : v1[x].e) {
          if (j != f) {
            for (int k : v2[i].e) {
              if (k != v2[i].f && v1[j].b[k]) {
                h.AddEdge(v1[j].r, v2[k].r);
              }
            }
          }
        }
        v1[x].b[i] = h.Flow() == _m;
      } else {
        v1[x].b[i] = !_m;
      }
    }
  }
  return v1[x].b[1];
}

bool T(int f, int x) {
  for (int i : v1[x].e) {
    if (i != f) {
      T(x, i);
    }
  }
  return ReT(f, x, -1);
}

bool Calc(int f, int x) {
  for (int i : v1[x].e) {
    if (i != f) {
      if (ReT(i, x, 0) || ReT(0, i, 1) || Calc(x, i) || ReT(x, i, 0) || ReT(0, x, 1)) {
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    for (int i = 1; i <= n; i++) {
      v1[i].e.clear();
    }
    for (int i = 1; i <= m; i++) {
      v2[i].e.clear();
    }
    cin >> n;
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v1[x].e.push_back(y), v1[y].e.push_back(x);
    }
    cin >> m;
    for (int i = 1, x, y; i < m; i++) {
      cin >> x >> y;
      v2[x].e.push_back(y), v2[y].e.push_back(x);
    }
    S(0, 1);
    cout << (T(0, 1) || Calc(0, 1) ? "Y\n" : "N\n");
  }
  return 0;
}
