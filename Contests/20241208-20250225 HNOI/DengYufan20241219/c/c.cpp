#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

int n, d, k1, k2, s, t;
LL ans;

class PrimalDuel {
  static const LL kMaxV = 60003, kMaxE = 89901, kInf = 1e18;
  struct E {
    int p, d;
    LL w, l;
  } e[kMaxE << 1];
  struct V {
    int et, p;
    LL h, d;
    bool b;
  } v[kMaxV];
  int s, t, o;

  void Spfa() {
    static queue<int> q;
    for (int i = 1; i <= t; i++) {
      v[i].h = i == s ? 0 : kInf;
      v[i].b = i == s;
    }
    for (q.push(s); !q.empty(); q.pop()) {
      int x = q.front();
      v[x].b = 0;
      for (int i = v[x].et; i; i = e[i].p) {
        int y = e[i].d;
        if (e[i].w && v[y].h > v[x].h + e[i].l) {
          v[y].h = v[x].h + e[i].l;
          if (!v[y].b) {
            v[y].b = 1, q.push(y);
          }
        }
      }
    }
  }

  bool Dij() {
    static priority_queue<pair<LL, int>> q;
    for (int i = 1; i <= t; i++) {
      v[i].d = i == s ? 0 : kInf;
      v[i].b = 0;
    }
    for (q.push({0, s}); !q.empty();) {
      int x = q.top().second;
      q.pop();
      if (v[x].b) {
        continue;
      }
      v[x].b = 1;
      for (int i = v[x].et; i; i = e[i].p) {
        int y = e[i].d;
        if (e[i].w && v[y].d > v[x].d + (e[i].l + v[x].h - v[y].h)) {
          v[y].d = v[x].d + (e[i].l + v[x].h - v[y].h);
          v[y].p = i, q.push({-v[y].d, y});
        }
      }
    }
    return v[t].b;
  }

 public:
  void Init(int _s, int _t) {  // _t should be maxinum of vertices
    s = _s, t = _t, o = 1;
    for (int i = 1; i <= t; i++) {
      v[i].et = 0;
    }
  }

  void AddEdge(int x, int y, LL w, LL l) {
    e[++o] = {v[x].et, y, w, l}, v[x].et = o;
    e[++o] = {v[y].et, x, 0, -l}, v[y].et = o;
  }

  LL Flow() {
    LL ans = 0;
    for (Spfa(); Dij();) {
      LL w = kInf;
      for (int i = 1; i <= t; i++) {
        v[i].h += v[i].d;
      }
      for (int i = t; i != s; i = e[v[i].p ^ 1].d) {
        w = min(w, e[v[i].p].w);
      }
      for (int i = t; i != s; i = e[v[i].p ^ 1].d) {
        e[v[i].p].w -= w, e[v[i].p ^ 1].w += w;
      }
      ans += w * v[t].h;
    }
    return ans;
  }
} pd;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  d = 3 * n * n, s = 2 * d + 1, t = s + 1, pd.Init(s, t);

  for (int i = 1; i <= n; i++) {  // 右左右左...
    int m = n + i - 1 << 1;
    for (int j = 1, w; j <= m; j++) {
      cin >> w;
      pd.AddEdge(k1 + (j + 1 >> 1), d + k2 + (j + 2 >> 1), 1, w);
    }
    k1 += n + i - 1, k2 += n + i;
  }
  for (int i = 1; i <= n; i++) {  // 左右左右...
    int m = n + n - i << 1;
    for (int j = 1, w; j <= m; j++) {
      cin >> w;
      pd.AddEdge(k1 + (j + 2 >> 1), d + k2 + (j + 1 >> 1), 1, w);
    }
    k1 += n + n - i + 1, k2 += n + n - i;
  }

  k1 = k2 = 0;

  for (int i = 1; i <= n; i++) {  // 下下下下...
    int m = n + i;
    k1 += n + i - 1;
    for (int j = 1, w; j <= m; j++) {
      cin >> w, ans += w;
      pd.AddEdge(d + k2 + j, k1 + j, 1, -w);
    }
    k2 += n + i;
  }
  for (int i = 1; i < n; i++) {  // 下下下下...
    int m = n + n - i;
    k1 += n + n - i + 1;
    for (int j = 1, w; j <= m; j++) {
      cin >> w, ans += w;
      pd.AddEdge(d + k2 + j, k1 + j, 1, -w);
    }
    k2 += n + n - i;
  }

  for (int i = 1; i <= n; i++) {
    pd.AddEdge(s, i, 1, 0);
    pd.AddEdge(d + d - n + i, t, 1, 0);
  }

  cout << ans + pd.Flow() << '\n';
  return 0;
}
