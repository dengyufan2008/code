#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("s.in");
ofstream cout("s.out");

const int kMaxN = 2e5 + 1, kMaxL = 18, kInf = 1e9;
struct E {
  int x, y;
} e[kMaxN];
struct V {
  int d, w, r, s, f[kMaxL], p[kMaxL];
  vector<int> e;
} v[kMaxN];
struct H {
  int x, l, r, w, o;
};
int n, m, q, d[kMaxN], c[kMaxN], ans[kMaxN];
vector<H> h;

void Add(int x) {
  for (int i = x; i <= n; i += i & -i) {
    d[i]++;
  }
}

int Ask(int x) {
  int ans = 0;
  for (int i = x; i >= 1; i -= i & -i) {
    ans += d[i];
  }
  return ans;
}

void S(int f, int x) {
  static int k = 0;
  v[x].d = v[x].w = v[f].d + 1;
  v[x].r = ++k, v[x].s = 1, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].e) {
    S(x, i), v[x].s += v[i].s;
  }
}

int Lca(int x, int y) {
  v[x].d < v[y].d ? swap(x, y) : void();
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

void T(int x) {
  v[x].s += v[x].r - 1;
  for (int i : v[x].e) {
    T(i), v[x].w = min(v[x].w, v[i].w);
  }
}

int F(int x, int d) {
  for (int i = 0; i < kMaxL; i++) {
    if (d >> i & 1) {
      x = v[x].f[i];
    }
  }
  return x;
}

int Calc(int x, int y) {
  if (x == y) {
    return 0;
  }
  int ans = 0;
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[v[x].p[i]].d > v[y].d) {
      x = v[x].p[i], ans |= 1 << i;
    }
  }
  x = v[x].p[0], ans++;
  return v[x].d <= v[y].d ? ans : -kInf;
}

int P(int x, int d) {
  for (int i = 0; i < kMaxL; i++) {
    if (d >> i & 1) {
      x = v[x].p[i];
    }
  }
  return x;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 2, x; i <= n; i++) {
    cin >> x, v[x].e.push_back(i);
  }
  S(0, 1), cin >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    int z = Lca(x, y);
    v[x].r > v[y].r ? swap(x, y) : void();
    v[x].w = min(v[x].w, v[z].d);
    v[y].w = min(v[y].w, v[z].d);
    e[i] = {x, y};
  }
  T(1);
  for (int i = 1; i <= n; i++) {
    v[i].p[0] = F(i, v[i].d - v[i].w);
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      v[j].p[i] = v[v[j].p[i - 1]].p[i - 1];
    }
  }
  cin >> q;
  for (int i = 1, x, y; i <= q; i++) {
    cin >> x >> y;
    int z = Lca(x, y);
    int wx = Calc(x, z), wy = Calc(y, z);
    ans[i] = wx + wy;
    if (ans[i] >= 0 && x != z && y != z) {
      int _x = P(x, wx - 1), _y = P(y, wy - 1);
      v[_x].r > v[_y].r ? swap(_x, _y) : void();
      h.push_back({v[_x].r - 1, v[_y].r, v[_y].s, -1, i});
      h.push_back({v[_x].s, v[_y].r, v[_y].s, 1, i});
    }
  }
  sort(e + 1, e + m + 1, [](E i, E j) {
    return v[i.x].r < v[j.x].r;
  });
  sort(h.begin(), h.end(), [](H i, H j) {
    return i.x < j.x;
  });
  for (int i = 0, j = 1; i < h.size(); i++) {
    for (; j <= m && v[e[j].x].r <= h[i].x; j++) {
      Add(v[e[j].y].r);
    }
    c[h[i].o] += h[i].w * (Ask(h[i].r) - Ask(h[i].l - 1));
  }
  for (int i = 1; i <= q; i++) {
    ans[i] -= c[i] > 0;
    cout << (ans[i] >= 0 ? ans[i] : -1) << '\n';
  }
  return 0;
}
