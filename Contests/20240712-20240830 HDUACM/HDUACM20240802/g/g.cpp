#include <fstream>
#include <set>

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 1e5 + 1;
struct V {
  int f;
  bool b;
  set<pair<int, int>> s;
} v[kMaxN];
int t, n, m, ans;
pair<int, int> e[kMaxN];

int GetRoot(int x) { return v[x].f == x ? x : v[x].f = GetRoot(v[x].f); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      v[i].f = i, v[i].b = 0, v[i].s.clear();
    }
    for (int i = 1; i < n; i++) {
      cin >> e[i].first >> e[i].second;
      e[i].first > e[i].second ? swap(e[i].first, e[i].second) : void();
    }
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y;
      int a = GetRoot(x), b = GetRoot(y);
      if (a != b) {
        v[a].s.size() > v[b].s.size() ? swap(a, b) : void();
        v[b].s.insert(v[a].s.begin(), v[a].s.end());
        v[a].f = b, v[a].s.clear();
      }
      v[b].s.insert({min(x, y), max(x, y)});
    }
    for (int i = 1; i < n; i++) {
      int x = GetRoot(e[i].first);
      if (x == GetRoot(e[i].second)) {
        v[x].b |= !v[x].s.count(e[i]);
      }
    }
    for (int i = 1; i <= n; i++) {
      ans += v[i].f == i, ans += v[i].b;
    }
    cout << ans << '\n', ans = 0;
  }
  return 0;
}
