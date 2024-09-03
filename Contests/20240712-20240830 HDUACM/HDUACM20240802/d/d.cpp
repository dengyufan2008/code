#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 1e5 + 1, kMaxM = 1e6 + 1, kMaxL = 17, kMaxV = 1e5;
struct V {
  int d, r, s, f[kMaxL];
  vector<int> e;
} v[kMaxN];
struct Q {
  int x, w, d;
} q[kMaxM];
int t, n, m, k, d[kMaxN], ans[kMaxM];
vector<int> l[kMaxN];

int Gcd(int x, int y) { return y ? Gcd(y, x % y) : x; }

void T(int f, int x) {
  v[x].d = v[f].d + 1, v[x].r = ++k, v[x].s = 1;
  v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i), v[x].s += v[i].s;
    }
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

void Add(int x, int y) {
  for (int i = x; i <= n; i += i & -i) {
    d[i] += y;
  }
}

int Ask(int x) {
  int ans = 0;
  for (int i = x; i >= 1; i -= i & -i) {
    ans += d[i];
  }
  return ans;
}

int Ask(int x, int y) { return Ask(y) - Ask(x - 1); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    k = 0;
    for (int i = 1; i <= kMaxV; i++) {
      l[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      d[i] = 0, v[i].e.clear();
    }
    cin >> n;
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y, v[x].e.push_back(y), v[y].e.push_back(x);
    }
    T(0, 1);
    for (int i = 1; i <= n; i++) {
      int x = n / i;
      for (int j = 1; j <= x; j++) {
        int y = min(x, kMaxV / (i * j));
        for (int k = j + 1; k <= y; k++) {
          if (Gcd(j, k) == 1) {
            l[i * j * k].push_back(Lca(i * j, i * k));
          }
        }
      }
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
      cin >> q[i].x >> q[i].w, q[i].d = i;
    }
    sort(q + 1, q + m + 1, [](Q i, Q j) {
      return i.w < j.w;
    });
    for (int i = 1, j = 1; i <= m; i++) {
      for (; j <= q[i].w; j++) {
        if (j <= n) {
          Add(v[j].r, 1);
        }
        for (int x : l[j]) {
          Add(v[x].r, 2);
        }
      }
      ans[q[i].d] = Ask(v[q[i].x].r, v[q[i].x].r + v[q[i].x].s - 1);
    }
    for (int i = 1; i <= m; i++) {
      cout << ans[i] << " \n"[i == m];
    }
  }
  return 0;
}
