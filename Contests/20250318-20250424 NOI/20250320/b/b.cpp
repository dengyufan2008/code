#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const LL kMaxN = 2.5e5 + 2, kInf = 1e18;
struct E {
  int a, b, pr, nt, p, q;
  LL s, c, d, f, g;
} e[kMaxN];
struct Q {
  int x, y, w, o;
} q[kMaxN << 2];
int n, m, k, w[kMaxN];
LL ans[kMaxN];
vector<int> h;
vector<pair<int, bool>> v[kMaxN];

class Seg {  // range: [0, n-1]
  struct V {
    int c, t;
    LL s;
  } v[kMaxN << 2];

  void Tag(int p, int t) {
    v[p].s += 1LL * t * v[p].c, v[p].t += t;
  }

  void Pushdown(int p) {
    Tag(p << 1, v[p].t), Tag(p << 1 | 1, v[p].t), v[p].t = 0;
  }

  void Change(int p, int l, int r, int x, bool y) {
    if (l == r) {
      v[p].c = y;
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, y);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, y);
    }
    v[p].c = v[p << 1].c + v[p << 1 | 1].c;
    v[p].s = v[p << 1].s + v[p << 1 | 1].s;
  }

  void Add(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return Tag(p, 1);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r);
    }
    v[p].c = v[p << 1].c + v[p << 1 | 1].c;
    v[p].s = v[p << 1].s + v[p << 1 | 1].s;
  }

  LL Ask(int p, int l, int r, int x) {
    if (r <= x) {
      return v[p].s;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    LL ans = Ask(p << 1, l, mid, x);
    if (mid < x) {
      ans += Ask(p << 1 | 1, mid + 1, r, x);
    }
    return ans;
  }

 public:
  void Active(int x) { Change(1, 0, n - 1, x, 1); }
  void Inactive(int x) { Change(1, 0, n - 1, x, 0); }
  void Add(int l, int r) { Add(1, 0, n - 1, l, r); }
  LL Ask(int x) { return Ask(1, 0, n - 1, x); }
} seg;

int FindLess(LL w) {
  int l = 0, r = h.size() - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (e[h[mid]].s <= w) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return r < 0 ? -1 : h[r];
}

int FindGreater(LL w) {
  int l = 0, r = h.size() - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (e[h[mid]].s >= w) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return r < 0 ? n + 1 : h[r];
}

void CalcE() {
  for (int i = 1; i <= n; i++) {
    e[i].s = e[i - 1].s + e[i].b;
  }
  e[0].c = e[0].f = -kInf;
  for (int i = 1; i <= n; i++) {
    e[i].c = max(e[i - 1].c, 0LL) + e[i].a;
    e[i].f = max(e[i - 1].f, e[i].c);
  }
  e[n + 1].d = e[n + 1].g = -kInf;
  for (int i = n; i >= 1; i--) {
    e[i].d = max(e[i + 1].d, 0LL) + e[i].a;
    e[i].g = max(e[i + 1].g, e[i].d);
  }
  h.clear();
  for (int i = 0; i <= n; i++) {
    for (; !h.empty() && e[h.back()].s <= e[i].s; h.pop_back()) {
    }
    e[i].pr = h.empty() ? -1 : h.back();
    h.push_back(i);
  }
  h.clear();
  for (int i = 0; i <= n; i++) {
    for (; !h.empty() && e[h.back()].s > e[i].s; h.pop_back()) {
    }
    e[i].p = FindLess(e[i].s - e[i + 1].g);
    h.push_back(i);
  }
  h.clear();
  for (int i = n; i >= 0; i--) {
    for (; !h.empty() && e[h.back()].s >= e[i].s; h.pop_back()) {
    }
    e[i].nt = h.empty() ? n + 1 : h.back();
    h.push_back(i);
  }
  h.clear();
  for (int i = n; i >= 0; i--) {
    for (; !h.empty() && e[h.back()].s < e[i].s; h.pop_back()) {
    }
    e[i].q = FindGreater(e[i].s + e[i].f);
    h.push_back(i);
  }
}

void CalcQ() {
  sort(q + 1, q + k + 1, [](Q i, Q j) {
    return i.y < j.y;
  });
  for (int i = 0; i + 1 < n; i++) {
    if (e[i].c <= 0 && e[i].q < e[i].nt) {
      v[e[i].q].push_back({i, 1});
      v[e[i].nt].push_back({i, 0});
    }
  }
  for (int i = 1, j = 1; i <= n; i++) {
    for (auto o : v[i]) {
      if (o.second) {
        seg.Active(o.first);
      } else {
        seg.Inactive(o.first);
      }
    }
    if (e[i].pr < min(e[i].p, i - 2) && e[i + 1].d <= 0) {
      seg.Add(e[i].pr + 1, min(e[i].p, i - 2));
    }
    for (; j <= k && q[j].y == i; j++) {
      ans[q[j].o] += q[j].w * seg.Ask(q[j].x);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a >> e[i].b;
  }
  CalcE();
  for (int i = 1; i <= n; i++) {
    w[i] = w[i - 1];
    if (e[i].b >= max(e[i - 1].f, e[i + 1].g) && max(e[i - 1].c, e[i + 1].d) <= 0) {
      w[i]++;
    }
  }
  for (int i = 1, l1, r1, l2, r2; i <= m; i++) {
    cin >> l1 >> r1 >> l2 >> r2, l2++, r2++;
    if (min(r1 + 1, r2) > max(l1, l2 - 1)) {
      ans[i] = w[min(r1 + 1, r2)] - w[max(l1, l2 - 1)];
    }
    q[++k] = {r1, r2, 1, i};
    if (l1 >= 1) {
      q[++k] = {l1 - 1, r2, -1, i};
    }
    if (l2 >= 2) {
      q[++k] = {r1, l2 - 1, -1, i};
    }
    if (l1 >= 1 && l2 >= 2) {
      q[++k] = {l1 - 1, l2 - 1, 1, i};
    }
  }
  CalcQ();
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
