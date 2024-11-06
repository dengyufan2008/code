#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e5 + 1;
struct Q {
  int t, l, r, o;
} q[kMaxN];
struct V {
  int t, x, w;
};
int n, m, a[kMaxN], pr[kMaxN], nt[kMaxN];
LL ans[kMaxN];
vector<pair<int, int>> l;
vector<V> v1, v2;

class H {
  LL d[kMaxN];

 public:
  void Add(int x, int y) {
    for (int i = x; i <= n; i += i & -i) {
      d[i] += y;
    }
  }

  LL Ask(int x) {
    LL ans = 0;
    for (int i = x; i >= 1; i -= i & -i) {
      ans += d[i];
    }
    return ans;
  }

  LL Ask(int x, int y) { return Ask(y) - Ask(x - 1); }
} h1, h2;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i].t >> q[i].l >> q[i].r, q[i].o = i;
  }
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.t < j.t;
  });
  for (int i = 1; i <= n; i++) {
    for (; !l.empty() && l.back().first <= a[i]; l.pop_back()) {
    }
    pr[i] = l.empty() ? 0 : l.back().second;
    l.push_back({a[i], i});
  }
  l.clear();
  for (int i = n; i >= 1; i--) {
    for (; !l.empty() && l.back().first < a[i]; l.pop_back()) {
    }
    nt[i] = l.empty() ? n + 1 : l.back().second;
    l.push_back({a[i], i});
  }
  l.clear();
  for (int i = 1; i <= n; i++) {
    if (pr[i] && i - pr[i] <= nt[i] - i) {
      for (int j = 0; j < i - pr[i]; j++) {
        v2.push_back({j, i, a[i]});
        v2.push_back({j + nt[i] - i, nt[i], -a[i]});
      }
    } else {
      for (int j = 0; j < nt[i] - i; j++) {
        v1.push_back({j, i + j, a[i]});
        if (pr[i]) {
          v1.push_back({j + i - pr[i], i + j, -a[i]});
        }
      }
    }
  }
  sort(v1.begin(), v1.end(), [](V i, V j) {
    return i.t < j.t;
  });
  sort(v2.begin(), v2.end(), [](V i, V j) {
    return i.t < j.t;
  });
  for (int i = 0, j = 1, k1 = 0, k2 = 0; i <= n; i++) {
    for (; k1 < v1.size() && v1[k1].t == i; k1++) {
      h1.Add(v1[k1].x, v1[k1].w);
    }
    for (; k2 < v2.size() && v2[k2].t == i; k2++) {
      h2.Add(v2[k2].x - i, v2[k2].w);
    }
    for (; j <= m && q[j].t == i; j++) {
      ans[q[j].o] = h1.Ask(q[j].l, q[j].r) + h2.Ask(q[j].l - i, q[j].r - i);
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
