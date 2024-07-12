#include <iostream>
#include <vector>

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 5e5 + 1, kMaxL = 19;
struct V {
  int r, d, f[kMaxL];
  vector<int> e;
} v[kMaxN];
int n, m, ans, a[kMaxN];

void T(int f, int x) {
  v[x].r = x, v[x].d = v[f].d + 1, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
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

int GetR(int x) { return v[x].r == x ? x : v[x].r = GetR(v[x].r); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, 1), ans = n;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    (x > n) && (x = a[x - n]), (y > n) && (y = a[y - n]);
    a[i] = Lca(x, y);
    for (x = GetR(x); v[x].d >= v[GetR(a[i])].d; x = GetR(v[x].f[0])) {
      v[x].r = GetR(a[i]), ans--;
    }
    for (y = GetR(y); v[y].d > v[GetR(a[i])].d; y = GetR(v[y].f[0])) {
      v[y].r = GetR(a[i]), ans--;
    }
    cout << ++ans << '\n';
  }
  return 0;
}
