#include <algorithm>
#include <fstream>
#include <queue>
#define PII pair<int, int>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e5 + 1, kMaxM = 16, kInf = 1e9;
int n, m, w, ans, p[kMaxN];
PII mx1, mx2;
vector<PII> a[kMaxN];

class PQ {
  priority_queue<PII> q1, q2;

  void Update() {
    while (!q2.empty() && q1.top() == q2.top()) {
      q1.pop(), q2.pop();
    }
  }

 public:
  void Push(PII x) { q1.push(x); }
  void Erase(PII x) { q2.push(x); }
  void Pop() { Update(), q1.pop(); }
  PII Top() { return Update(), q1.top(); }
  bool Empty() { return Update(), q1.empty(); }
} q1, q2;

void Update(PII &x, PII y) {
  if (x.first < y.first) {
    x = y;
  }
}

void Calc(bool o) {
  PII w1 = mx1, w2 = mx2;
  if (!q1.Empty()) {
    Update(w1, q1.Top()), Update(w2, q2.Top());
  }
  if (w1.second != w2.second) {
    if (!o) {
      ans = min(ans, w1.first + w2.first);
    } else if (ans == w1.first + w2.first) {
      for (int i = 1; i <= n; i++) {
        cout << (a[i][p[i]].first - a[i][p[i]].second) / w / 2 << " \n"[i == n];
      }
      exit(0);
    }
    return;
  }
  int mx = -kInf;
  static int g[kMaxN];
  for (int i = 1; i <= n; i++) {
    if (i != w1.second) {
      int mn = kInf;
      for (int j = 0; j < a[i].size(); j++) {
        if (a[i][j].first <= w1.first && a[i][j].second <= w2.first) {
          int u = max(a[i][j].first + w2.first, a[i][j].second + w1.first);
          if (mn > u) {
            mn = u, g[i] = j;
          }
        }
      }
      mx = max(mx, mn);
    } else {
      g[i] = p[i];
    }
  }
  if (!o) {
    ans = min(ans, mx);
  } else if (ans == mx) {
    for (int i = 1; i <= n; i++) {
      cout << (a[i][g[i]].first - a[i][g[i]].second) / w / 2 << " \n"[i == n];
    }
    exit(0);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> w, ans = kInf;
  for (int i = 1; i <= n; i++) {
    for (int j = 1, x; j <= m; j++) {
      cin >> x, a[i].push_back({x + j * w, x - j * w});
    }
  }
  for (int i = 1; i <= n; i++) {
    static vector<PII> t;
    sort(a[i].begin(), a[i].end()), t.push_back(a[i][0]);
    for (int j = 1, mn = a[i][0].second; j < m; j++) {
      if (a[i][j].second < mn) {
        mn = a[i][j].second, t.push_back(a[i][j]);
      }
    }
    a[i].swap(t), t.clear();
  }
  for (int o : {0, 1}) {
    mx1 = mx2 = {-kInf, 0};
    while (!q1.Empty()) {
      q1.Pop(), q2.Pop();
    }
    for (int i = 1; i <= n; i++) {
      p[i] = 0;
      if (a[i].size() > 1) {
        q1.Push({a[i][0].first, i}), q2.Push({a[i][0].second, i});
      } else {
        Update(mx1, {a[i][0].first, i}), Update(mx2, {a[i][0].second, i});
      }
    }
    for (Calc(o); !q2.Empty() && q2.Top().first > mx2.first; Calc(o)) {
      int x = q2.Top().second;
      q1.Erase({a[x][p[x]].first, x}), q2.Erase({a[x][p[x]].second, x});
      p[x]++;
      if (p[x] + 1 < a[x].size()) {
        q1.Push({a[x][p[x]].first, x}), q2.Push({a[x][p[x]].second, x});
      } else {
        Update(mx1, {a[x][p[x]].first, x}), Update(mx2, {a[x][p[x]].second, x});
      }
    }
    if (!o) {
      cout << ans << '\n';
    }
  }
  return 0;
}
