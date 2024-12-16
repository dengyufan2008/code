#include <fstream>
#include <queue>
#define LL long long
#define LLL __int128_t

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxT = 10, kMaxN = 100, kInf = 1e9;
struct P {
  int x, y, o;
} p[kMaxT];
struct A {
  int x, y, c;
} a[kMaxN + kMaxT];
struct E {
  int x, y, w, p, o;
} e[kMaxN * 6 - 12];
int t, n, m, w, b[kMaxN * 2 - 4], ans[kMaxT];
vector<int> l[kMaxN * 2 - 4];
queue<int> q;

class Dinic {
  struct E {
    int p, d, w;
  } e[kMaxN * 20 - 38];
  struct V {
    int d, et, nt;
  } v[kMaxN * 2 - 1];
  int s, t, k;
  queue<int> q;

  bool Bfs() {
    for (int i = 0; i <= t; i++) {
      v[i].d = i == s, v[i].nt = v[i].et;
    }
    for (q.push(s); !q.empty(); q.pop()) {
      for (int i = v[q.front()].et; ~i; i = e[i].p) {
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
    for (int &i = v[x].nt; ~i && in; in && (i = e[i].p)) {
      if (e[i].w && v[x].d + 1 == v[e[i].d].d) {
        int t = Dfs(e[i].d, min(in, e[i].w));
        e[i].w -= t, e[i ^ 1].w += t;
        in -= t, out += t;
      }
    }
    return out;
  }

 public:
  void Reset(int _s, int _t) {
    s = _s, t = _t, k = 0;
    for (int i = 0; i <= t; i++) {
      v[i].et = -1;
    }
  }

  void AddEdge(int x, int y, int w) {
    e[k] = {v[x].et, y, w}, v[x].et = k++;
    e[k] = {v[y].et, x, 0}, v[y].et = k++;
  }

  void AddEdge2(int x, int y, int w) {
    e[k] = {v[x].et, y, w}, v[x].et = k++;
    e[k] = {v[y].et, x, w}, v[y].et = k++;
  }

  int Flow() {
    int ans = 0;
    for (; Bfs(); ans += Dfs(s, kInf)) {
    }
    return ans;
  }
} dinic;

LL Dot(int o, int x, int y) {
  return 1LL * (a[x].x - a[o].x) * (a[y].x - a[o].x) +
         1LL * (a[x].y - a[o].y) * (a[y].y - a[o].y);
}

LL Cross(int o, int x, int y) {
  return 1LL * (a[x].x - a[o].x) * (a[y].y - a[o].y) -
         1LL * (a[x].y - a[o].y) * (a[y].x - a[o].x);
}

LL Dis(int x, int y) {
  return 1LL * (a[x].x - a[y].x) * (a[x].x - a[y].x) +
         1LL * (a[x].y - a[y].y) * (a[x].y - a[y].y);
}

int Sign(LL x) { return x > 0 ? 1 : -1; }

bool Check(int x, int y, int p, int q) {
  if (Sign(Cross(y, p, x)) * Sign(Cross(y, q, x)) > 0) {
    return Cross(y, p, q) > 0 || Cross(y, p, q) == 0 && Dis(y, p) > Dis(y, q);
  } else {
    return Cross(y, q, x) > 0;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> n >> m;
  for (int i = 0; i < t; i++) {
    cin >> p[i].x >> p[i].y;
    a[n + i] = {p[i].x, p[i].y};
    ans[i] = kInf;
  }
  for (int i = 0; i < n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  for (int i = 0, x, y, w; i < m; i++) {
    cin >> x >> y >> w, x--, y--;
    a[x].c++, a[y].c++;
    e[i * 2] = {x, y, w};
    e[i * 2 + 1] = {y, x, w};
  }
  for (int i = 0; i < n; i++) {
    if (a[i].c == 1) {
      q.push(i);
    }
  }
  for (; !q.empty(); q.pop()) {
    a[q.front()].c = 0;
    for (int i = 0; i < m << 1; i++) {
      if (e[i].x == q.front() && a[e[i].y].c) {
        if (--a[e[i].y].c == 1) {
          q.push(e[i].y);
        }
        break;
      }
    }
  }
  for (int i = 0; i < m << 1; i++) {
    e[i].p = e[i].o = -1;
    if (!a[e[i].x].c || !a[e[i].y].c) {
      continue;
    }
    for (int j = 0; j < m << 1; j++) {
      if (a[e[j].x].c && a[e[j].y].c && e[i].y == e[j].x &&
          (Cross(e[i].y, e[i].x, e[j].y) != 0 || Dot(e[i].y, e[i].x, e[j].y) < 0)) {
        if (e[i].p == -1 || Check(e[i].x, e[i].y, e[e[i].p].y, e[j].y)) {
          e[i].p = j;
        }
      }
    }
    e[i].p == -1 && (e[i].p = i ^ 1);
  }
  for (int i = 0, j; i < m << 1; i++) {
    if (e[i].o == -1 && a[e[i].x].c && a[e[i].y].c) {
      LLL s = Cross(0, e[i].x, e[e[i].p].x);
      for (j = e[i].p; j != i; j = e[j].p) {
        s += Cross(0, e[j].x, e[e[j].p].x);
      }
      if (s > 0) {
        l[w].push_back(e[i].x), e[i].o = w;
        for (j = e[i].p; j != i; j = e[j].p) {
          l[w].push_back(e[j].x), e[j].o = w;
        }
        w++;
      } else {
        e[i].o = -2;
        for (j = e[i].p; j != i; j = e[j].p) {
          e[j].o = -2;
        }
      }
    }
  }
  for (int i = 0; i < m << 1; i++) {
    e[i].o == -2 && (e[i].o = w);
  }
  for (int i = 0; i < t; i++) {
    for (int j = 0; j < w; j++) {
      bool o = Cross(n + i, l[j].back(), l[j].front()) > 0;
      for (int k = 1; k < l[j].size() && o; k++) {
        o &= Cross(n + i, l[j][k - 1], l[j][k]) > 0;
      }
      if (o) {
        p[i].o = j;
        break;
      }
    }
  }
  for (int s = 1; s < 1 << t; s++) {
    int pop = __builtin_popcount(s) - 1;
    dinic.Reset(w + 1, w + 2);
    dinic.AddEdge(w + 1, w, kInf);
    for (int i = 0; i < m << 1; i += 2) {
      if (e[i].o != e[i ^ 1].o) {
        dinic.AddEdge2(e[i].o, e[i ^ 1].o, e[i].w);
      }
    }
    for (int i = 0; i < t; i++) {
      (s >> i & 1) && (b[p[i].o] = s);
    }
    for (int i = 0; i < w; i++) {
      if (b[i] == s) {
        dinic.AddEdge(i, w + 2, kInf);
      }
    }
    ans[pop] = min(ans[pop], dinic.Flow());
  }
  for (int i = t - 2; i >= 0; i--) {
    ans[i] = min(ans[i], ans[i + 1]);
  }
  for (int i = 0; i < t; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
