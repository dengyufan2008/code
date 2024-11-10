#include <algorithm>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 5e5 + 1, kMaxV = 1e9;
struct A {
  int x, y;
  mutable int w;
  bool operator<(const A &a) const {
    return x < a.x;
  }
} a[kMaxN];
int t, n, m, f[kMaxN];
long long ans;
vector<A> e;
set<A> s;

auto Split(int t) {
  auto p = s.lower_bound({t, 0, 0});
  if (p != s.end() && p->x == t) {
    return p;
  }
  A o = *--p;
  s.erase(p), s.insert({o.x, t - 1, o.w});
  return s.insert({t, o.y, o.w}).first;
}

int GetRoot(int x) { return f[x] == x ? x : f[x] = GetRoot(f[x]); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n, m = ans = 0, e.clear(), s.clear(), s.insert({1, kMaxV, 0});
    for (int i = 1; i <= n; i++) {
      cin >> a[i].x >> a[i].y >> a[i].w, f[i] = i;
    }
    sort(a + 1, a + n + 1, [](A i, A j) {
      return i.w < j.w;
    });
    for (int i = 1; i <= n; i++) {
      auto y = Split(a[i].y + 1), x = Split(a[i].x);
      for (auto j = x; j != y; j++) {
        j->w ? e.push_back({j->w, i, a[i].w - a[j->w].w}) : void();
      }
      s.erase(x, y), s.insert({a[i].x, a[i].y, i});
    }
    sort(e.begin(), e.end(), [](A i, A j) {
      return i.w < j.w;
    });
    for (A i : e) {
      if (GetRoot(i.x) != GetRoot(i.y)) {
        f[GetRoot(i.x)] = GetRoot(i.y);
        m++, ans += i.w;
      }
    }
    cout << (m == n - 1 ? ans : -1) << '\n';
  }
  return 0;
}
