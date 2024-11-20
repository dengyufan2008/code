#include <algorithm>
#include <fstream>
#include <set>
#include <vector>
#define LL long long
#define LLL __int128_t

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 3e5 + 1, kInf = 1e9;
struct S {
  int l, r;
  mutable int c;
  bool operator<(const S &s) const {
    return l < s.l;
  }
};
struct E {
  int x, y, w;
};
int n, d[kMaxN];
LL m, ans;
set<S> s;
vector<E> e;

auto Split(int x) {
  auto p = s.lower_bound({x, 0, 0});
  if (p->l == x) {
    return p;
  }
  S o = *--p;
  s.erase(p), s.insert({o.l, x - 1, o.c});
  return s.insert({x, o.r, o.c}).first;
}

bool C(int x) {
  LLL f = 0;
  LL g = 0, c = 0;
  int w = 0, mn = kInf;
  for (int i = 1; i <= n; i++) {
    d[i] = 0;
  }
  for (int i = 1, j = 1, k = 0; i <= n; i++) {
    for (; k < e.size() && e[k].x == i; k++) {
      d[e[k].y] += e[k].w;
      g += 1LL * e[k].w * min(e[k].y, j - 1);
      j <= e[k].y && (w += e[k].w);
    }
    for (; j <= i && w >= x; j++) {
      mn = min(mn, w), g += w, w -= d[j];
    }
    f += g, c += j - 1;
  }
  if (c >= m) {
    ans = min((LLL)ans, f - (LLL)(c - m) * mn);
    return 1;
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, s.insert({1, kInf, 0});
  for (int i = 1, l, r; i <= n; i++) {
    cin >> l >> r;
    auto q = Split(r), p = Split(l);
    for (auto j = p; j != q; j++) {
      if (j->c) {
        e.push_back({j->c, j->c, j->r - j->l + 1});
        e.push_back({i, j->c, j->l - j->r - 1});
      }
    }
    s.erase(p, q), s.insert({l, r - 1, i});
  }
  for (auto i : s) {
    if (i.c) {
      e.push_back({i.c, i.c, i.r - i.l + 1});
    }
  }
  sort(e.begin(), e.end(), [](E i, E j) {
    return i.x < j.x;
  });
  ans = 1LL * kInf * kInf;
  for (int l = 1, r = kInf; l <= r;) {
    int mid = l + r >> 1;
    if (C(mid)) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << ans << '\n';
  return 0;
}
