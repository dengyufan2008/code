#include <algorithm>
#include <fstream>
#include <set>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 4e5 + 1;
struct E {
  int x, y;
  LL w;
};
struct V {
  int s;
  LL d;
  vector<pair<int, int>> e, g;
} v[kMaxN];
int n, m, s;
int r1, r2, w;  // r1: 靠下的, r2: 靠上的, w: 边权
LL ans;
vector<E> e;
set<pair<LL, int>> q[2];

class DSU {
  int f[kMaxN];

 public:
  void Init(int n) {
    for (int i = 1; i <= n; i++) {
      f[i] = i;
    }
  }

  int GetRoot(int x) {
    return f[x] == x ? x : f[x] = GetRoot(f[x]);
  }

  void Merge(int x, int y) {
    x = GetRoot(x), y = GetRoot(y), f[x] = y;
  }
} dsu;

void AddG(int x, int y, int w) {
  v[x].g.push_back({y, w}), v[y].g.push_back({x, w});
}

void CalcG(int f, int x) {
  if (v[x].e.size() <= 3) {
    for (auto i : v[x].e) {
      if (i.first != f) {
        AddG(x, i.first, i.second);
      }
    }
  } else {
    int p = x;
    for (auto i : v[x].e) {
      if (i.first != f) {
        m++, AddG(m, p, 0), p = m;
        AddG(m, i.first, i.second);
      }
    }
  }
  for (auto i : v[x].e) {
    if (i.first != f) {
      CalcG(x, i.first);
    }
  }
}

void CalcR(int f, int x) {
  v[x].s = 1;
  for (auto i : v[x].g) {
    if (i.first != f) {
      CalcR(x, i.first), v[x].s += v[i.first].s;
      if (!r1 || abs(s - v[i.first].s * 2) < abs(s - v[r1].s * 2)) {
        r1 = i.first, r2 = x, w = i.second;
      }
    }
  }
}

void DelG(int x, int y) {
  static vector<pair<int, int>> g;
  for (auto i : v[x].g) {
    if (i.first != y) {
      g.push_back(i);
    }
  }
  v[x].g.swap(g), g.clear();
  for (auto i : v[y].g) {
    if (i.first != x) {
      g.push_back(i);
    }
  }
  v[y].g.swap(g), g.clear();
}

void CalcD(int f, int x, bool o) {
  if (x <= n) {
    q[o].insert({v[x].d, x});
  }
  for (auto i : v[x].g) {
    if (i.first != f) {
      v[i.first].d = v[x].d + i.second;
      CalcD(x, i.first, o);
    }
  }
}

void CalcE(int f, int x, bool o) {
  if (x <= n) {
    auto p = q[o].lower_bound({-v[x].d, 0});
    if (p != q[o].end()) {
      e.push_back({x, p->second, abs(v[x].d + p->first)});
    }
    if (p != q[o].begin()) {
      p--, e.push_back({x, p->second, abs(v[x].d + p->first)});
    }
  }
  for (auto i : v[x].g) {
    if (i.first != f) {
      CalcE(x, i.first, o);
    }
  }
}

void Divide() {
  DelG(r1, r2);
  q[0].clear(), v[r1].d = 0, CalcD(0, r1, 0);
  q[1].clear(), v[r2].d = w, CalcD(0, r2, 1);
  CalcE(0, r1, 1), CalcE(0, r2, 0);
  int _s = v[r1].s, _r1 = r1, _r2 = r2;
  if (s - _s > 1) {
    s -= _s, r1 = 0, CalcR(0, _r2), Divide();
  }
  if (_s > 1) {
    s = _s, r1 = 0, CalcR(0, _r1), Divide();
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  m = n, CalcG(0, 1);
  s = m, CalcR(0, 1), Divide();
  sort(e.begin(), e.end(), [](E i, E j) {
    return i.w < j.w;
  });
  dsu.Init(m);
  for (E i : e) {
    int x = dsu.GetRoot(i.x), y = dsu.GetRoot(i.y);
    if (x != y) {
      ans += i.w, dsu.Merge(x, y);
    }
  }
  cout << ans << '\n';
  return 0;
}
