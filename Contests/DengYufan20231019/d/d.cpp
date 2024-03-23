#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kMaxN = 2e5 + 1, kMaxL = 18;
struct V {
  int r, l, b, d, f[kMaxL];
  bool f1, f2;
  vector<int> e, g;
} v[kMaxN];
int n, m, q, _r, _v;
vector<int> l;

void R(int x) {
  v[x].r = v[x].l = ++_r;
  l.push_back(x);
  for (int i : v[x].e) {
    if (v[i].r) {
      v[x].l = min(v[x].l, v[i].r);
    } else {
      R(i), v[x].l = min(v[x].l, v[i].l);
      if (v[x].r == v[i].l) {
        v[++_v].g.push_back(x), v[x].g.push_back(_v);
        while (l.back() != i) {
          v[_v].g.push_back(l.back()), v[l.back()].g.push_back(_v);
          l.pop_back();
        }
        v[_v].g.push_back(i), v[i].g.push_back(_v);
        l.pop_back();
      }
    }
  }
}

void S(int f, int x) {
  v[x].d = v[f].d + 1, v[x].f[0] = f, v[x].f1 = 1;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].g) {
    if (i != f) {
      S(x, i), v[x].f1 &= v[i].f1;
    }
  }
  if (x > n) {
    for (int i : v[f].e) {
      v[i].b = x;
    }
    for (int i : v[x].g) {
      if (i != f) {
        v[x].f1 &= v[i].b == x;
      }
    }
  }
}

void T(int f, int x) {
  int c1 = 0;
  for (int i : v[x].g) {
    v[i].b = -x;
    if (i != f) {
      c1 += v[i].f1;
    }
  }
  for (int i : v[x].g) {
    if (i != f) {
      v[i].f2 = v[x].f2 & (c1 - v[i].f1 == v[x].g.size() - (f > 0) - 1);
      if (i <= n) {
        int c2 = 0;
        for (int j : v[i].e) {
          c2 += v[j].b == -x;
        }
        v[i].f2 &= c2 == v[x].g.size() - 1;
      }
      T(x, i);
    }
  }
}

int Lca(int x, int y) {
  if (v[x].d < v[y].d) {
    swap(x, y);
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = v[x].f[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? x : v[x].f[0];
}

int F(int x, int d) {
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (d >> i & 1) {
      x = v[x].f[i];
    }
  }
  return x;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  _v = n, R(1), S(0, 1), v[1].f2 = 1, T(0, 1);
  for (int i = 1; i <= n; i++) {
    if (v[i].f1 && v[i].f2) {
      for (int j = 1; j <= q; j++) {
        cout << "Yes\n";
      }
      return 0;
    }
  }
  for (int i = 1, x, y; i <= q; i++) {
    cin >> x >> y;
    if (Lca(x, y) == x) {
      int z = F(y, v[y].d - v[x].d - 1);
      cout << (v[z].f1 ? "Yes\n" : "No\n");
    } else {
      cout << (v[x].f2 ? "Yes\n" : "No\n");
    }
  }
  return 0;
}
