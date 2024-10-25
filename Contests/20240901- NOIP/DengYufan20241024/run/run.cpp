#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("run.in");
ofstream cout("run.out");

const int kMaxN = 3e5 + 2;
int t, u;

namespace Sub1 {
struct E {
  int p, d;
  bool b;
} e[kMaxN * 4];
struct V {
  int c, et, nt;
} v[kMaxN];
int n, m, k;
vector<int> l;
vector<vector<int>> ans;

void T(int p, int x) {
  for (int &i = v[x].nt; i;) {
    if (!e[i].b) {
      e[i].b = e[i ^ 1].b = 1;
      int j = i;
      i = e[i].p, T(j, e[j].d);
    } else {
      i = e[i].p;
    }
  }
  l.push_back(p);
}

int main() {
  while (t--) {
    cin >> n >> m, k = 1, ans.clear();
    for (int i = 1; i <= n + 1; i++) {
      v[i].c = v[i].et = 0;
    }
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y, v[x].c++, v[y].c++;
      e[++k] = {v[x].et, y}, v[x].et = k;
      e[++k] = {v[y].et, x}, v[y].et = k;
    }
    for (int i = 1; i <= n; i++) {
      if (v[i].c & 1) {
        e[++k] = {v[i].et, n + 1}, v[i].et = k;
        e[++k] = {v[n + 1].et, i}, v[n + 1].et = k;
      }
    }
    for (int i = 1; i <= n + 1; i++) {
      v[i].nt = v[i].et;
    }
    for (int i = n + 1; i >= 1; i--) {
      T(0, i), l.pop_back();
      if (!l.empty()) {
        static vector<int> r;
        reverse(l.begin(), l.end());
        for (auto j : l) {
          if (j / 2 <= m) {
            r.push_back(j);
          } else if (!r.empty()) {
            ans.push_back(r), r.clear();
          }
        }
        if (!r.empty()) {
          ans.push_back(r), r.clear();
        }
        l.clear();
      }
    }
    cout << ans.size() << '\n';
    for (auto &i : ans) {
      cout << e[i.front() ^ 1].d << ' '
           << e[i.back()].d << ' '
           << i.size() << '\n';
      for (int j : i) {
        cout << j / 2 << ' ';
      }
      cout << '\n';
    }
  }
  return 0;
}
}  // namespace Sub1

namespace Sub2 {
struct A {
  int x, y, z;
  int o1, o2;
};
int n, m;
vector<A> a;

namespace CalcEdge {
struct E {
  int p, d;
} e[kMaxN << 1];
struct V {
  int c, f, s, r, et;
} v[kMaxN];
int k;
bool shit;

int GetRoot(int x) {
  return v[x].f == x ? x : v[x].f = GetRoot(v[x].f);
}

void Merge(int x, int y) {
  x = GetRoot(x), y = GetRoot(y);
  v[y].s++, x != y ? v[x].f = y, v[y].s += v[x].s : 0;
}

int Find2(int f, int x) {
  int p = 0;
  v[x].r = ++k;
  for (int o = v[x].et; o; o = e[o].p) {
    int i = e[o].d;
    if (i != f && v[i].r < v[x].r) {
      int w = !v[i].r ? Find2(x, i) : 0;
      if (w) {
        a.push_back({x, i, e[w].d, o, w});
      } else if (p) {
        a.push_back({e[p].d, x, i, p ^ 1, o});
        p = 0;
      } else {
        p = o;
      }
    }
  }
  return p;
}

int main() {
  cin >> n >> m, k = shit = 0, a.clear();
  for (int i = 1; i <= n; i++) {
    v[i].c = v[i].s = v[i].r = v[i].et = 0, v[i].f = i;
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[x].c++, v[y].c++, Merge(x, y);
    e[i * 2] = {v[x].et, y}, v[x].et = i * 2;
    e[i * 2 + 1] = {v[y].et, x}, v[y].et = i * 2 + 1;
  }
  for (int i = 1; i <= n; i++) {
    if (GetRoot(i) == i && v[i].s % 2) {
      cout << -1 << '\n', shit = 1;
      break;
    }
  }
  if (shit) {
    return 1;
  }
  for (int i = 1; i <= n; i++) {
    if (!v[i].r) {
      Find2(0, i);
    }
  }
  return 0;
}
}  // namespace CalcEdge

namespace CalcAns {
struct E {
  int p, d, mid, o1, o2;
  bool b;
} e[kMaxN];
struct V {
  int c, et, nt;
} v[kMaxN];
int k;
vector<int> l;
vector<vector<int>> ans;

void T(int p, int x) {
  for (int &i = v[x].nt; i;) {
    if (!e[i].b) {
      e[i].b = e[i ^ 1].b = 1;
      int j = i;
      i = e[i].p, T(j, e[j].d);
    } else {
      i = e[i].p;
    }
  }
  l.push_back(p);
}

int main() {
  k = 1, m /= 2, ans.clear();
  for (int i = 1; i <= n + 1; i++) {
    v[i].c = v[i].et = 0;
  }
  for (A i : a) {
    v[i.x].c++, v[i.z].c++;
    e[++k] = {v[i.x].et, i.z, i.y, i.o1, i.o2}, v[i.x].et = k;
    e[++k] = {v[i.z].et, i.x, i.y, i.o2 ^ 1, i.o1 ^ 1}, v[i.z].et = k;
  }
  for (int i = 1; i <= n; i++) {
    if (v[i].c & 1) {
      e[++k] = {v[i].et, n + 1}, v[i].et = k;
      e[++k] = {v[n + 1].et, i}, v[n + 1].et = k;
    }
  }
  for (int i = 1; i <= n + 1; i++) {
    v[i].nt = v[i].et;
  }
  for (int i = n + 1; i >= 1; i--) {
    T(0, i), l.pop_back();
    if (!l.empty()) {
      static vector<int> r;
      reverse(l.begin(), l.end());
      for (auto j : l) {
        if (j / 2 <= m) {
          r.push_back(j);
        } else if (!r.empty()) {
          ans.push_back(r), r.clear();
        }
      }
      if (!r.empty()) {
        ans.push_back(r), r.clear();
      }
      l.clear();
    }
  }
  cout << ans.size() << '\n';
  for (auto &i : ans) {
    cout << e[i.front() ^ 1].d << ' '
         << e[i.back()].d << ' '
         << i.size() * 2 << '\n';
    for (int j : i) {
      cout << e[j].o1 / 2 << ' ' << e[j].o2 / 2 << ' ';
    }
    cout << '\n';
  }
  return 0;
}
}  // namespace CalcAns

int main() {
  while (t--) {
    CalcEdge::main() || CalcAns::main();
  }
  return 0;
}
}  // namespace Sub2

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> u;
  if (u) {
    return Sub2::main();
  } else {
    return Sub1::main();
  }
}
