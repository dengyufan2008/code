#include <chrono>
#include <fstream>
#include <random>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("break.in");
ofstream cout("break.out");

const LL kInf = 1e18;
int t, n, m;
vector<int> a;
mt19937_64 Rand(chrono::steady_clock().now().time_since_epoch().count());

namespace Solve1 {
const int kMaxN = 1002;
struct V {
  int w, wt, l, r;
  LL f, mn;
  unsigned LL o;
} v[kMaxN];
int k, s;
LL ans;

void TagW(int p, int wt) {
  v[p].w += wt, v[p].wt += wt;
}

void Pushdown(int p) {
  if (v[p].wt) {
    if (v[p].l) {
      TagW(v[p].l, v[p].wt);
    }
    if (v[p].r) {
      TagW(v[p].r, v[p].wt);
    }
    v[p].wt = 0;
  }
}

void Update(int p) {
  v[p].mn = v[p].f;
  if (v[p].l) {
    v[p].mn = min(v[p].mn, v[v[p].l].mn);
  }
  if (v[p].r) {
    v[p].mn = min(v[p].mn, v[v[p].r].mn);
  }
}

pair<int, int> Split(int p, int x) {
  if (!p) {
    return {0, 0};
  }
  Pushdown(p);
  if (v[p].w <= x) {
    auto q = Split(v[p].r, x);
    v[p].r = q.first, Update(p);
    return {p, q.second};
  } else {
    auto q = Split(v[p].l, x);
    v[p].l = q.second, Update(p);
    return {q.first, p};
  }
}

int Merge(int p, int q) {
  if (!p || !q) {
    return p | q;
  }
  Pushdown(p), Pushdown(q);
  if (v[p].o < v[q].o) {
    v[p].r = Merge(v[p].r, q);
    return Update(p), p;
  } else {
    v[q].l = Merge(p, v[q].l);
    return Update(q), q;
  }
}

LL Calc() {
  k = s = 1, v[1].w = 1, v[1].o = Rand();
  v[1].wt = v[1].l = v[1].r = v[1].f = v[1].mn = 0;
  for (int i = 1; i < n; i++) {
    v[++k] = {1, 0, 0, 0, v[s].mn + a[i], v[s].mn + a[i], Rand()};
    auto p = Split(s, m - 1);
    TagW(p.first, 1);
    s = Merge(k, p.first);
  }
  return v[s].mn;
}

int main() {
  ans = kInf;
  for (int i = 1; i <= m; i++) {
    ans = min(ans, Calc() + a.front());
    int x = a.back();
    a.pop_back(), a.insert(a.begin(), x);
  }
  cout << ans << '\n';
  return 0;
}
}  // namespace Solve1

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    bool o = 1;
    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      o &= a[i] <= 2;
    }
    Solve1::main();
  }
  return 0;
}
