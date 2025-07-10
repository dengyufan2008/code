#include <algorithm>
#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e6 + 1;
int n, m, a[kMaxN], w[kMaxN], l[kMaxN];
int c1[kMaxN], c2[kMaxN];
LL ans[kMaxN];

class PrimalDuel {
  static const int kMaxV = 1e6 + 10, kMaxE = 3e6 + 10;
  static const LL kInf = 1e18;
  struct E {
    int p, d, w, l;
  } e[kMaxE << 1];
  struct V {
    int et, p;
    LL d;
    bool b;
  } v[kMaxV];
  int n, s, t, o;

  bool Dij() {
    static priority_queue<pair<LL, int>> q;
    for (int i = 1; i <= n; i++) {
      v[i].d = i == s ? 0 : kInf;
      v[i].b = 0;
    }
    for (; !q.empty(); q.pop()) {
    }
    for (q.push({0, s}); !q.empty();) {
      int x = q.top().second;
      q.pop();
      if (v[x].b) {
        continue;
      } else if (x == t) {
        return 1;
      }
      v[x].b = 1;
      for (int i = v[x].et; i; i = e[i].p) {
        int y = e[i].d;
        if (e[i].w && v[y].d > v[x].d + e[i].l) {
          v[y].d = v[x].d + e[i].l, v[y].p = i;
          q.push({-v[y].d, y});
        }
      }
    }
    return 0;
  }

 public:
  void Init(int _n, int _s, int _t) {
    n = _n, s = _s, t = _t, o = 1;
    for (int i = 1; i <= n; i++) {
      v[i].et = 0;
    }
  }

  void AddEdge(int x, int y, int w, int l) {
    e[++o] = {v[x].et, y, w, l}, v[x].et = o;
    e[++o] = {v[y].et, x, 0, -l}, v[y].et = o;
  }

  void Flow(LL *ans) {
    for (int p = 1; Dij(); p++) {
      for (int i = t; i != s; i = e[v[i].p ^ 1].d) {
        e[v[i].p].w--, e[v[i].p ^ 1].w++;
      }
      ans[p] = ans[p - 1] + v[t].d;
    }
  }
} pd;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n, n <<= 1;
  for (int i = 1; i <= n; i++) {
    cin >> w[i], l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) {
    return w[i] < w[j];
  });
  a[l[1]] = 1;
  for (int i = 2; i <= n; i++) {
    a[l[i]] = a[l[i - 1]] + (w[l[i - 1]] < w[l[i]]);
  }
  sort(w + 1, w + n + 1), m = unique(w + 1, w + n + 1) - w - 1;
  for (int i = 1; i <= n >> 1; i++) {
    c1[a[i]]++, c2[a[i + (n >> 1)]]++;
  }
  pd.Init(m + 2, m + 1, m + 2);
  for (int i = 1; i <= m; i++) {
    pd.AddEdge(m + 1, i, c1[i], 0);
    pd.AddEdge(i, m + 2, c2[i], 0);
  }
  for (int i = 2; i <= m; i++) {
    pd.AddEdge(i - 1, i, n, w[i] - w[i - 1]);
    pd.AddEdge(i, i - 1, n, w[i] - w[i - 1]);
  }
  pd.Flow(ans);
  for (int i = 1; i <= n >> 1; i++) {
    cout << ans[i] << " \n"[i == n >> 1];
  }
  return 0;
}
