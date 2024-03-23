#include <fstream>
#include <vector>

using namespace std;

ifstream cin("regression.in");
ofstream cout("regression.out");

const int kMaxN = 1e5 + 1, kMaxL = 16;
struct D {
  int w, l, r;
} d[kMaxN * 48];
struct V {
  int d, s, f, p, t[kMaxL];
  bool b;
  vector<int> e;
} v[kMaxN];
int n, m, w, r, k;

void T(int f, int x) {
  v[x].d = v[f].d + 1, v[x].t[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].t[i] = v[v[x].t[i - 1]].t[i - 1];
  }
  for (int i : v[x].e) {
    if (i != f) {
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
      x = v[x].t[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].t[i] != v[y].t[i]) {
      x = v[x].t[i], y = v[y].t[i];
    }
  }
  return x == y ? x : v[x].t[0];
}

int Dis(int x, int y) {
  return v[x].d + v[y].d - v[Lca(x, y)].d * 2;
}

void CalcR(int f, int x, int n) {
  int mx = 0;
  v[x].s = 1;
  for (int i : v[x].e) {
    if (i != f && !v[i].b) {
      CalcR(x, i, n);
      v[x].s += v[i].s;
      mx = max(mx, v[i].s);
    }
  }
  if (max(mx, n - v[x].s) * 2 <= n) {
    r = x;
  }
}

void Build(int x) {
  v[x].b = 1;
  for (int i : v[x].e) {
    if (!v[i].b) {
      CalcR(0, i, v[i].s), CalcR(0, r, v[i].s);
      v[r].f = x, Build(r);
    }
  }
}

void Change(int &p, int l, int r, int x, int y) {
  !p && (p = ++k);
  if (l == r) {
    d[p].w = y;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(d[p].l, l, mid, x, y);
  } else {
    Change(d[p].r, mid + 1, r, x, y);
  }
  d[p].w = min(d[d[p].l].w, d[d[p].r].w);
}

int Ask(int p, int l, int r, int x, int y) {
  if (!p) {
    return n;
  } else if (l >= x && r <= y) {
    return d[p].w;
  }
  int mid = l + r >> 1, ans = n;
  if (mid >= x) {
    ans = min(ans, Ask(d[p].l, l, mid, x, y));
  }
  if (mid < y) {
    ans = min(ans, Ask(d[p].r, mid + 1, r, x, y));
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> w >> w;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  d[0].w = n, T(0, 1), CalcR(0, 1, n), CalcR(0, r, n), Build(r);
  for (int i = 1, o, x, y, z, p; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      x ^= p * w;
      for (int j = x; j; j = v[j].f) {
        Change(v[j].p, 1, n, x, Dis(j, x));
      }
    } else if (o == 2) {
      x ^= p * w;
      for (int j = x; j; j = v[j].f) {
        Change(v[j].p, 1, n, x, n);
      }
    } else {
      cin >> y >> z;
      z ^= p * w;
      int ans = n;
      for (int j = z; j; j = v[j].f) {
        ans = min(ans, Ask(v[j].p, 1, n, x, y) + Dis(j, z));
      }
      if (ans == n) {
        cout << -1 << '\n';
      } else {
        cout << (p = ans) << '\n';
      }
    }
  }
  return 0;
}
