// 写的一坨
#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 2001, kMaxM = 2e6 + 1;
int n, m;
pair<int, int> e[kMaxM];

int Read() {
  int x = 0, c = getchar();
  while (c < 48 || c > 57) {
    c = getchar();
  }
  while (c > 47 && c < 58) {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
  return x;
}

void Print(int x) {
  if (x < 10) {
    putchar(48 + x);
  } else {
    Print(x / 10);
    putchar(48 + x % 10);
  }
}

namespace Sub1 {
struct V {
  int r, _r, d, t, c, f, s, _s, e[kMaxN];
  bool b;
} v[kMaxN];
int s, ans[kMaxM];
vector<int> l, _l;

int GetRoot(int x) {
  return v[x].f == x ? x : v[x].f = GetRoot(v[x].f);
}

int Calc(int s) { return s == 2 ? 2 : 1; }

void Merge(int x, int y) {
  x = GetRoot(x), y = GetRoot(y);
  if (x != y) {
    s -= Calc(v[x].s) + Calc(v[y].s);
    v[x].f = y, v[y].s += v[x].s;
    s += Calc(v[y].s);
  }
}

void S(int x, int s) {
  v[x].b = 1, v[x].r = s, v[s]._s += v[x].s;
  for (int i = 1; i <= n; i++) {
    if (v[x].e[i] + v[i].e[x] < v[x].s * v[i].s && !v[i].b) {
      S(i, s);
    }
  }
}

void T(int x) {  // tarjan 真能写对吗
  static int k = 0;
  v[x].b = 0, v[x].d = v[x].t = ++k;
  l.push_back(x);
  for (int i = 1; i <= n; i++) {
    if (v[i].r == i && v[x].e[i]) {
      if (v[i].b) {
        T(i);
        v[x].t = min(v[x].t, v[i].t);
      } else if (!v[i]._r) {
        v[x].t = min(v[x].t, v[i].d);
      }
    }
  }
  if (v[x].d == v[x].t) {
    for (; l.back() != x; l.pop_back()) {
      v[x].s += v[l.back()].s, v[l.back()].s = 0;
      v[l.back()]._r = x;
    }
    v[x]._r = x, l.pop_back();
  }
}

int main(int _x = 1, int _s = 1) {
  for (int i = 1; i <= m; i++) {
    v[e[i].first].e[e[i].second]++;
  }
  for (int i = 1; i <= n; i++) {
    v[i].s = 1;
  }
  v[_x].s = _s;                   // 补全 sub2 缩的点
  for (int i = 1; i <= n; i++) {  // 缩补图无向连通块
    if (!v[i].b) {
      S(i, i);
    }
  }
  for (int i = 1; i <= n; i++) {
    v[i].s = v[i]._s;
  }
  for (int i = 1; i <= n; i++) {  // 代表元继承边
    for (int j = 1; j <= n; j++) {
      if (i != v[i].r || j != v[j].r) {
        v[v[i].r].e[v[j].r] += v[i].e[j];
        v[i].e[j] = 0;
      }
    }
  }
  for (int i = 1; i <= n; i++) {  // 缩原图强连通
    if (v[i].r == i && v[i].b) {
      T(i);
    }
  }
  for (int i = 1; i <= n; i++) {
    v[i].r = v[v[i].r]._r;
  }
  for (int i = 1; i <= n; i++) {  // 代表元继承边
    for (int j = 1; j <= n; j++) {
      if (i != v[i].r || j != v[j].r) {
        v[v[i].r].e[v[j].r] += v[i].e[j];
        v[i].e[j] = 0;
      }
    }
  }
  for (int i = 1; i <= n; i++) {  // 统计出度
    if (v[i].r == i) {
      v[i].f = i, s += Calc(v[i].s), l.push_back(i);
      for (int j = 1; j <= n; j++) {
        if (j != i && v[j].r == j) {
          v[i].c += v[i].e[j] > 0;
        }
      }
    }
  }
  _l.resize(l.size());
  for (int i : l) {
    _l[v[i].c] = i;
  }
  l.swap(_l), _l.clear();
  for (int i = m; i >= 1; i--) {  // 加反向边
    ans[i] = s;
    int x = v[e[i].first].r, y = v[e[i].second].r;
    for (int z = GetRoot(y); v[z].c < v[x].c; z = GetRoot(z)) {
      Merge(z, l[v[z].c + 1]);
    }
  }
  for (int i = 1; i <= m; i++) {
    Print(ans[i]), putchar(10);
  }
  return 0;
}
}  // namespace Sub1

namespace Sub2 {
const int kMaxN = 2e5 + 1;
int s, d[kMaxN], o[kMaxN];
bool b[kMaxN];
pair<int, int> a[kMaxM];

int main() {  // 将入度+出度最小的点补图上的邻居缩起来
  for (int i = 1; i <= m; i++) {
    a[i].first = Read(), a[i].second = Read();
    d[a[i].first]++, d[a[i].second]++;
  }
  for (int i = 1; i <= n; i++) {
    if (!s || d[i] < d[s]) {
      s = i;
    }
  }
  for (int i = 1; i <= m; i++) {
    if (a[i].first == s || a[i].second == s) {
      b[a[i].first ^ a[i].second ^ s] = 1;
    }
  }
  b[s] = 1;
  for (int i = 1; i <= n; i++) {
    o[i] = o[i - 1] + b[i];
  }
  for (int i = 1; i <= m; i++) {
    int x = a[i].first, y = a[i].second;
    !b[x] && (x = s), !b[y] && (y = s);
    e[i] = {o[x], o[y]};
  }
  int _n = n;
  n = o[n];
  return Sub1::main(o[s], _n - d[s]);
}
}  // namespace Sub2

int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  n = Read(), m = Read();
  if (n <= 2000) {
    for (int i = 1; i <= m; i++) {
      e[i].first = Read(), e[i].second = Read();
    }
    return Sub1::main();
  } else {
    return Sub2::main();
  }
  return 0;
}
