#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("calm.in");
ofstream cout("calm.out");

const int kMaxN = 3e5 + 1;
struct D {
  int l, r, o;
} d[kMaxN * 20];
struct V {
  int s;             // 线段树的根
  int d, _d;         // 深度, 离散化后的深度
  int o, f;          // 子树中编号 <= mid 的最浅点的深度, f <= mid 的最浅点的深度
  bool g, h;         // g, h 是否 <= mid
  vector<int> e, p;  // 边, 走 a-1 条边到达的子孙
} v[kMaxN];
int n, m, s, a, b;

void Push(int &p, int l, int r, int x, int o) {
  !p && (d[++m] = d[0], p = m);
  if (l == r) {
    d[p].o = o;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Push(d[p].l, l, mid, x, o);
  } else {
    Push(d[p].r, mid + 1, r, x, o);
  }
  d[p].o = d[p].l ? d[d[p].l].o : d[d[p].r].o;
}

void Pop(int &p, int l, int r) {
  if (l == r) {
    p = 0;
    return;
  }
  int mid = l + r >> 1;
  if (d[p].l) {
    Pop(d[p].l, l, mid);
  } else {
    Pop(d[p].r, mid + 1, r);
  }
  if (d[p].l || d[p].r) {
    d[p].o = d[p].l ? d[d[p].l].o : d[d[p].r].o;
  } else {
    p = 0;
  }
}

void Merge(int &p, int q, int l, int r) {
  if (!p || !q) {
    p |= q;
    return;
  }
  int mid = l + r >> 1;
  Merge(d[p].l, d[q].l, l, mid);
  Merge(d[p].r, d[q].r, mid + 1, r);
  d[p].o = d[p].l ? d[d[p].l].o : d[d[p].r].o;
}

int Top(int p) { return d[p].o; }

void Init(int f, int x) {
  static vector<int> l, e;
  v[x].d = v[f].d + 1, l.push_back(x);
  l.size() >= a ? v[l[l.size() - a]].p.push_back(x) : void();
  for (int i : v[x].e) {
    if (i != f) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  for (int i : v[x].e) {
    Init(x, i);
  }
  l.pop_back();
}

void Init() {
  static int o[kMaxN];
  Init(0, s);
  for (int i = 1; i <= n; i++) {
    o[i] = i;
  }
  sort(o + 1, o + n + 1, [](int i, int j) {
    return v[i].d < v[j].d;
  });
  for (int i = 1; i <= n; i++) {
    v[o[i]]._d = i;
  }
}

void CalcF(int x) {
  bool p = 1;
  for (int i : v[x].e) {
    p &= v[i].p.empty();
  }
  if (p) {
    v[x].o <= v[x].d + b && (v[x].f = v[x].d);
    return;
  }
  bool f = 1;
  for (int i : v[x].e) {
    for (int j : v[i].p) {
      f &= v[j].h;
    }
  }
  f && (v[x].f = v[x].d);
}

void CalcG(int x) {
  static bool p[kMaxN], o[kMaxN];
  static int g[kMaxN];
  int cp = 0, co = 0, cg = 0, cs = 0;
  for (int i = 0; i < v[x].e.size(); i++) {
    p[i] = v[v[x].e[i]].p.empty();
    o[i] = v[v[x].e[i]].o <= v[x].d + b;
    g[i] = 0;
    for (int j : v[v[x].e[i]].p) {
      g[i] += v[j].h;
    }
    cp += p[i], co += o[i], cg += g[i], cs += v[v[x].e[i]].p.size();
  }
  for (int i = 0; i < v[x].e.size(); i++) {
    if (cp - p[i] == v[x].e.size() - 1) {
      v[v[x].e[i]].g = v[x].o == v[x].d || co - o[i];
    } else {
      v[v[x].e[i]].g = cg - g[i] == cs - v[v[x].e[i]].p.size();
    }
  }
}

void CalcH(int x) {
  if (v[x].f <= v[x].d + b) {
    v[x].h = 1;
  } else {
    Push(v[x].s, 1, n, v[x]._d, x);
  }
  for (int i : v[x].e) {
    if (v[i].g) {
      int y = Top(v[i].s);
      while (y && v[y].d <= v[x].d + b) {
        v[y].h = 1, Pop(v[i].s, 1, n), y = Top(v[i].s);
      }
    }
  }
  for (int i = 0, j = kMaxN * 2; i < v[x].e.size(); i++) {
    int y = v[x].e[i], z = Top(v[y].s);
    while (z && v[z].d <= v[x].d * 2 + b - j) {
      v[z].h = 1, Pop(v[y].s, 1, n), z = Top(v[y].s);
    }
    j = min(j, v[y].f);
  }
  for (int i = v[x].e.size() - 1, j = kMaxN * 2; i >= 0; i--) {
    int y = v[x].e[i], z = Top(v[y].s);
    while (z && v[z].d <= v[x].d * 2 + b - j) {
      v[z].h = 1, Pop(v[y].s, 1, n), z = Top(v[y].s);
    }
    j = min(j, v[y].f);
  }
  for (int i : v[x].e) {
    Merge(v[x].s, v[i].s, 1, n);
  }
}

void Dp(int x, int mid) {
  v[x].s = v[x].h = 0, v[x].o = v[x].f = kMaxN * 2;
  for (int i : v[x].e) {
    Dp(i, mid);
    v[x].o = min(v[x].o, v[i].o);
    v[x].f = min(v[x].f, v[i].f);
  }
  x <= mid && (v[x].o = v[x].d);
  CalcF(x), CalcG(x), CalcH(x);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> s >> a >> b;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  if (a <= b) {
    cout << 1 << '\n';
    return 0;
  }
  Init();
  int l = 1, r = n;
  while (l <= r) {
    int mid = l + r >> 1;
    m = 0, Dp(s, mid);
    if (v[s].f == 1) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << l << '\n';
  return 0;
}
