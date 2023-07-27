#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <iostream>
#include <set>
#include <vector>
#define LL long long

using namespace std;

const LL kMaxN = 1e5 + 1, kInf = 4e18;
struct V {
  LL s, c, f;
  vector<pair<LL, LL>> e;
  set<pair<LL, LL>> q[2];
} v[kMaxN];
LL t, n, k, q;

LL Cross(pair<LL, LL> o, pair<LL, LL> x, pair<LL, LL> y) {
  return (x.first - o.first) * (y.second - o.second) - (x.second - o.second) * (y.first - o.first);
}

void Insert(LL x, pair<LL, LL> f) {
  auto p1 = v[x].q[0].lower_bound({f.first, -kInf});
  if (p1 != v[x].q[0].end() && p1->first == f.first && p1->second < f.second) {
    return;
  }
  auto p3 = p1;
  if (p1 != v[x].q[0].end()) {
    for (p1++; p1 != v[x].q[0].end() && Cross(f, *p3, *p1) <= 0; p1++) {
      v[x].q[1].erase({-p3->first, p3->second}), v[x].q[0].erase(p3), p3 = p1;
    }
  }
  auto p2 = v[x].q[1].lower_bound({-f.first, -kInf}), p4 = p2;
  if (p2 != v[x].q[1].end()) {
    for (p2++; p2 != v[x].q[1].end() && Cross(f, {-p4->first, p4->second}, {-p2->first, p2->second}) >= 0; p2++) {
      v[x].q[0].erase({-p4->first, p4->second}), v[x].q[1].erase(p4), p4 = p2;
    }
  }
  p3 = v[x].q[0].lower_bound({f.first, -kInf}), p4 = v[x].q[1].lower_bound({-f.first, -kInf});
  if (p3 == v[x].q[0].end() || p4 == v[x].q[1].end() || Cross(*p3, {-p4->first, p4->second}, f) > 0) {
    v[x].q[0].insert(f), v[x].q[1].insert({-f.first, f.second});
  }
}

void S(LL f, LL x) {
  for (auto i : v[x].e) {
    if (i.first != f) {
      v[i.first].s = v[x].s + i.second;
      S(x, i.first);
      v[x].c += v[i.first].c;
    }
  }
  for (auto &i : v[x].e) {
    if (i.first != f && (v[x].e[0].first == f || v[v[x].e[0].first].c < v[i.first].c)) {
      swap(v[x].e[0], i);
    }
  }
}

void T(LL f, LL x) {
  for (auto i : v[x].e) {
    if (i.first != f) {
      T(x, i.first);
    }
  }
  if (v[x].e.size() > 1 - !f) {
    v[x].q[0] = v[v[x].e[0].first].q[0], v[x].q[1] = v[v[x].e[0].first].q[1];
    v[v[x].e[0].first].q[0].clear(), v[v[x].e[0].first].q[1].clear();
    for (auto i : v[x].e) {
      if (i.first != f && i.first != v[x].e[0].first) {
        for (auto j : v[i.first].q[0]) {
          Insert(x, j);
        }
        v[i.first].q[0].clear(), v[i.first].q[1].clear();
      }
    }
    if (v[x].q[0].size() == 1) {
      auto p = v[x].q[0].lower_bound({-kInf, -kInf});
      v[x].f = p->second - p->first * p->first + (p->first - v[x].s - k) * (p->first - v[x].s - k);
    } else {
      LL l = -kInf, r = kInf;
      while (l <= r) {
        LL mid = l + r >> 1;
        auto p1 = v[x].q[0].lower_bound({mid, -kInf}), p2 = v[x].q[1].upper_bound({-mid, kInf});
        if (p1 != v[x].q[0].end() && (p2 == v[x].q[1].end() || p1->second - p2->second < 2 * (v[x].s + k) * (p1->first + p2->first))) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      auto p = v[x].q[0].lower_bound({r, -kInf});
      v[x].f = p->second - p->first * p->first + (p->first - v[x].s - k) * (p->first - v[x].s - k);
    }
  }
  Insert(x, {v[x].s, v[x].s * v[x].s + v[x].f});
}

int main() {
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    for (LL i = 1; i <= n; i++) {
      v[i].e.clear();
    }
    cin >> n >> k;
    for (LL i = 1, x, y, z; i < n; i++) {
      cin >> x >> y >> z;
      v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
    }
    cin >> q;
    for (LL i = 1, r; i <= q; i++) {
      cin >> r;
      for (LL i = 1; i <= n; i++) {
        v[i].s = v[i].f = 0, v[i].c = 1;
        v[i].q[0].clear(), v[i].q[1].clear();
      }
      S(0, r), T(0, r);
      cout << v[r].f << '\n';
    }
  }
  return 0;
}
// Too Slow
