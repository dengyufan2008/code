#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 601, kMaxM = kMaxN << 1, kInf = 114514;
int t, n, m, k, k1, k2;
pair<int, int> a[kMaxN];

class Dinic {
 public:
  struct E {
    int p, d, w;
  } e[kMaxM + kMaxN << 1];
  struct V {
    int d, et, nt;
  } v[kMaxM];

 private:
  int n, m, s, t;

  bool Bfs() {
    static queue<int> q;
    for (int i = 1; i <= n; i++) {
      v[i].d = i == s, v[i].nt = v[i].et;
    }
    for (q.push(s); !q.empty(); q.pop()) {
      int x = q.front();
      for (int i = v[x].et; i; i = e[i].p) {
        if (e[i].w && !v[e[i].d].d) {
          v[e[i].d].d = v[x].d + 1;
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

 public:
  void Init(int _n) {
    n = _n, m = 1;
    fill(&v[1], &v[n] + 1, v[0]);
  }

  void AddEdge(int x, int y, int w) {
    e[++m] = {v[x].et, y, w}, v[x].et = m;
    e[++m] = {v[y].et, x, 0}, v[y].et = m;
  }

  int Flow(int _s, int _t, int w) {
    int ans = 0;
    for (s = _s, t = _t; ans < w && Bfs(); ans += Dfs(s, w - ans)) {
    }
    return ans;
  }
} dinic;

void Input() {
  static int d[kMaxM], l[kMaxM], o[kMaxM];
  cin >> n >> m >> k1 >> k2;
  for (int i = 1; i <= n + m; i++) {
    cin >> d[i * 2 - 1] >> d[i * 2];
  }
  for (int i = 1; i <= n + m << 1; i++) {
    l[i] = i;
  }
  sort(l + 1, l + (n + m << 1) + 1, [](int i, int j) {
    return d[i] < d[j];
  });
  for (int i = 1; i <= n + m << 1; i++) {
    o[l[i]] = o[l[i - 1]] + (d[l[i - 1]] < d[l[i]]);
  }
  for (int i = 1; i <= n + m; i++) {
    a[i] = {o[i * 2 - 1], o[i * 2]};
  }
  k = o[l[n + m << 1]];
}

bool Check() {
  static int w1[kMaxM], w2[kMaxM];
  fill(&w1[1], &w1[k] + 1, 0);
  fill(&w2[1], &w2[k] + 1, 0);
  for (int i = 1; i <= n; i++) {
    w1[a[i].first]++, w1[a[i].second]--;
  }
  for (int i = n + 1; i <= n + m; i++) {
    w2[a[i].first]++, w2[a[i].second]--;
  }
  for (int i = 1; i <= k; i++) {
    w1[i] += w1[i - 1], w2[i] += w2[i - 1];
  }
  dinic.Init(k);
  for (int i = n + m; i >= n + 1; i--) {
    dinic.AddEdge(a[i].first, a[i].second, 1);
  }
  for (int i = 1; i < k; i++) {
    if (w1[i] + w2[i] - k1 <= k2) {
      dinic.AddEdge(i, i + 1, k1 + k2 - w1[i] - w2[i]);
    } else {
      cout << "NO\n";
      return 0;
    }
  }
  if (dinic.Flow(1, k, k2) == k2) {
    cout << "YES\n";
    return 1;
  } else {
    cout << "NO\n";
    return 0;
  }
}

void Print() {
  static int p[kMaxM], d[kMaxM], ans[kMaxM];
  static vector<pair<int, int>> l[kMaxM], r[kMaxM];
  for (int i = 1; i <= k; i++) {
    int &j = p[i] = dinic.v[i].et;
    for (; j & 1; j = dinic.e[j].p) {
    }
    j = dinic.e[j].p;
  }
  for (int i = 1; i <= n; i++) {
    l[a[i].first].push_back({a[i].second, i});
  }
  for (int i = n + 1; i <= n + m; i++) {
    int &j = p[a[i].first];
    for (; j & 1; j = dinic.e[j].p) {
    }
    if (dinic.e[j].w) {
      l[a[i].first].push_back({a[i].second, i});
    } else {
      r[a[i].first].push_back({a[i].second, i});
    }
    j = dinic.e[j].p;
  }
  fill(&d[1], &d[k1 + k2] + 1, 0);
  for (int i = 1; i <= k; i++) {
    for (auto j : l[i]) {
      for (int u = 1; u <= k1; u++) {
        if (d[u] <= i) {
          d[u] = j.first, ans[j.second] = u;
          break;
        }
      }
    }
    l[i].clear();
    for (auto j : r[i]) {
      for (int u = k1 + 1; u <= k1 + k2; u++) {
        if (d[u] <= i) {
          d[u] = j.first, ans[j.second] = u;
          break;
        }
      }
    }
    r[i].clear();
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
  for (int i = n + 1; i <= n + m; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    Input(), Check() ? Print() : void();
  }
  return 0;
}
