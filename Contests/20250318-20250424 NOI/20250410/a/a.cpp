// http://qoj.ac/problem/10009
#include <algorithm>
#include <iostream>
#include <queue>
#define LL long long

using namespace std;

const int kMaxN = 1e5 + 1;
const LL kInf = 1e18;
struct A {
  int x, y, c, o;
} a[kMaxN];
int n, m, k;

class Dij {
  static const int kMaxE = kMaxN * 400, kMaxV = kMaxN * 40;
  struct E {
    int p, d, w;
  } e[kMaxE];
  struct V {
    int et;
    LL d;
    bool b;
  } v[kMaxV];
  int _e;
  priority_queue<pair<LL, int>> q;

  void Update(int x, LL d) {
    if (v[x].d > d) {
      v[x].d = d, q.push({-d, x});
    }
  }

 public:
  void AddEdge(int x, int y, int w) {
    e[++_e] = {v[x].et, y, w}, v[x].et = _e;
  }

  void Run(int s) {
    for (int i = 1; i <= k; i++) {
      v[i].d = kInf;
    }
    int c = 0;
    for (Update(s, 0); c < n && !q.empty();) {
      int x = q.top().second;
      q.pop();
      if (v[x].b) {
        continue;
      }
      v[x].b = 1, c += x <= n;
      for (int i = v[x].et; i; i = e[i].p) {
        Update(e[i].d, v[x].d + e[i].w);
      }
    }
  }

  LL Ask(int x) { return v[x].d; }
} dij;

void Build() {
  static vector<pair<int, int>> l;
  for (int u = 0; u < 2; u++) {
    l.clear();
    sort(a + 1, a + n + 1, [](A i, A j) {
      return i.x < j.x || i.x == j.x && i.c < j.c;
    });
    for (int i = 1, j = 1; i <= n; i = j) {
      for (; j <= n && a[i].c == a[j].c; j++) {
      }
      l.push_back({i, j - 1});
    }
    for (int i = 0; i < l.size(); i++) {
      if (i > 0) {
        k++;
        for (int j = l[i].first; j <= l[i].second; j++) {
          dij.AddEdge(a[j].o, k, a[j].x - a[l[i].first].x);
        }
        for (int j = l[i - 1].first; j <= l[i - 1].second; j++) {
          dij.AddEdge(k, a[j].o, a[l[i].first].x - a[j].x);
        }
      }
      if (i + 1 < l.size()) {
        k++;
        for (int j = l[i].first; j <= l[i].second; j++) {
          dij.AddEdge(a[j].o, k, a[l[i].second].x - a[j].x);
        }
        for (int j = l[i + 1].first; j <= l[i + 1].second; j++) {
          dij.AddEdge(k, a[j].o, a[j].x - a[l[i].second].x);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      swap(a[i].x, a[i].y);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, k = n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y >> a[i].c, a[i].o = i;
  }
  Build(), dij.Run(1);
  sort(a + 1, a + n + 1, [](A i, A j) {
    return i.o < j.o;
  });
  for (int i = 2; i <= n; i++) {
    LL ans = max(abs(a[i].x - a[1].x), abs(a[i].y - a[1].y));
    cout << min(dij.Ask(i), ans) << '\n';
  }
  return 0;
}
