#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

ifstream cin("mo.in");
ofstream cout("mo.out");

const int kMaxN = 5e5 + 1;
struct A {
  int l, r;
} a[kMaxN];
struct Q {
  int l, r, o;
} q[kMaxN];
struct E {
  int l, r;
  mutable int w;
  bool operator<(const E &e) const {
    return l < e.l;
  }
};
int n, m, k, d[kMaxN], ans[kMaxN];
set<E> s;

void Add(int x, int y) {
  for (int i = x + 1; i <= m; i += i & -i) {
    d[i] += y;
  }
}

int Ask(int x) {
  int ans = 0;
  for (int i = x + 1; i >= 1; i -= i & -i) {
    ans += d[i];
  }
  return ans;
}

auto Split(int x) {
  if (x > n) {
    return s.end();
  }
  auto p = s.lower_bound({x});
  if (p->l == x) {
    return p;
  }
  E e = *--p;
  s.erase(p), s.insert({e.l, x - 1, e.w});
  return s.insert({x, e.r, e.w}).first;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i].l >> a[i].r;
  }
  cin >> k;
  for (int i = 1; i <= k; i++) {
    cin >> q[i].l >> q[i].r, q[i].o = i;
  }
  sort(q + 1, q + k + 1, [](Q i, Q j) {
    return i.r < j.r;
  });
  s.insert({1, n, 0}), Add(0, n);
  for (int i = 1, j = 1; i <= m; i++) {
    if (a[i].l < a[i].r) {
      auto y = Split(a[i].r + 1), x = Split(a[i].l);
      int w = m;
      for (auto j = x; j != y; j++) {
        w = min(w, j->w), Add(j->w, j->l - j->r - 1);
      }
      s.erase(x, y);
      s.insert({a[i].l, a[i].r - 1, i}), Add(i, a[i].r - a[i].l);
      s.insert({a[i].r, a[i].r, w}), Add(w, 1);
    }
    for (; j <= k && q[j].r == i; j++) {
      ans[q[j].o] = Ask(q[j].l - 1);
    }
  }
  for (int i = 1; i <= k; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
