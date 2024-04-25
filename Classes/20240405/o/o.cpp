#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("o.in");
ofstream cout("o.out");

const int kMaxN = 2e5 + 1, kMaxM = 1e6 + 1;
struct V {
  int s;
  bool b;
  vector<pair<int, int>> e;
} v[kMaxN];
struct Q {
  int l, r, d;
} q[kMaxM];
int n, m, s, r;
LL ans[kMaxM];
vector<pair<int, LL>> l, t;
vector<pair<int, int>> w;

void CalcR(int f, int x) {
  int mx = 0;
  v[x].s = 0;
  for (auto i : v[x].e) {
    if (i.first != f && !v[i.first].b) {
      CalcR(x, i.first);
      v[x].s += v[i.first].s;
      mx = max(mx, v[i.first].s);
    }
  }
  if (max(mx, s - v[x].s) * 2 <= s) {
    r = x;
  }
}

void CalcD(int f, int x, LL d) {
  l.push_back({x, d});
  for (auto i : v[x].e) {
    if (i.first != f) {
      CalcD(x, i.first, d + i.second);
    }
  }
}

void Divide() {
  v[r].b = 1, l.clear();
  for (auto i : v[r].e) {
    if (!v[i.first].b) {
      CalcD(0, i.first, i.second);
    }
  }
  sort(l.begin(), l.end());
  for (int o : {1, -1}) {
    t.clear();
    for (int i = ~o ? 0 : l.size() - 1; ~o ? i < l.size() : i >= 0; i += o) {
      for (; !t.empty() && t.back().second > l[i].second; t.pop_back()) {
      }
      if (!t.empty()) {
        int x = t.back().first, y = l[i].first;
        w.push_back({min(x, y), max(x, y)});
      }
      t.push_back(l[i]);
    }
  }
  int _s = s - v[r].s;
  for (auto i : v[r].e) {
    if (!v[i.first].b) {
      s = min(v[i.first].s, _s), CalcR(0, i.first), Divide();
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z});
    v[y].e.push_back({x, z});
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> q[i].l >> q[i].r;
  }
  s = n, CalcR(0, 1), Divide();
  sort(w.begin(), w.end());
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.l < j.l || i.l == j.l && i.r < j.r;
  });
  for (int i = n, j = w.size() - 1, k = m; i >= 1; i--) {
    for (; j >= 0 && w[j].first == i; j--) {
      seg.CheckMin(w[j].second, Dis(w[j].first, w[j].second));
    }
    for (; k >= 1 && q[k].l == i; k--) {
      ans[q[k].d] = seg.Ask(1, q[k].r);
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
