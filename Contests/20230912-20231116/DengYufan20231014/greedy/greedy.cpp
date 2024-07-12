#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("greedy.in");
ofstream cout("greedy.out");

const LL kMaxN = 2e5 + 1, kMaxL = 18;
struct V {
  LL d, l, fl, s, r, f[kMaxL];
  vector<pair<LL, LL>> e;
} v[kMaxN];
LL n, m, q, a[kMaxN];

void T(LL f, LL x) {
  v[x].d = v[f].d + 1, v[x].l = v[f].l + v[x].fl, v[x].s = 1, v[x].r = ++m, v[x].f[0] = f, a[m] = x;
  for (LL i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (auto i : v[x].e) {
    if (i.first != f) {
      v[i.first].fl = i.second;
      T(x, i.first);
      v[x].s += v[i.first].s;
    }
  }
}

LL Lca(LL x, LL y) {
  if (v[x].d < v[y].d) {
    swap(x, y);
  }
  for (LL i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = v[x].f[i];
    }
  }
  for (LL i = kMaxL - 1; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? x : v[x].f[0];
}

LL Dis(LL x, LL y) {
  return v[x].l + v[y].l - v[Lca(x, y)].l * 2;
}

void R(LL f, LL x, LL l) {
  v[x].l += l;
  for (auto i : v[x].e) {
    if (i.first != f) {
      R(x, i.first, l);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> q;
  for (LL i = 2, x, y; i <= n; i++) {
    cin >> x >> y;
    v[x].e.push_back({i, y});
  }
  T(0, 1);
  for (LL i = 1, o, x, y; i <= n; i++) {
    cin >> o >> x >> y;
    if (o == 1) {
      LL f = Lca(x, y);
      for (LL j = x; j != f; j = v[j].f[0]) {
        v[j].fl = -v[j].fl;
        R(v[j].f[0], j, v[j].fl * 2);
      }
      for (LL j = y; j != f; j = v[j].f[0]) {
        v[j].fl = -v[j].fl;
        R(v[j].f[0], j, v[j].fl * 2);
      }
    } else if (o == 2) {
      LL ans = Dis(x, y);
      for (LL i = 1; i < v[x].s; i++) {
        ans = min(ans, Dis(a[v[x].r + i], y));
      }
      cout << ans << '\n';
    } else {
      LL ans = Dis(x, y);
      for (LL i = 0; i < v[x].s; i++) {
        for (LL j = !i; j < v[y].s; j++) {
          ans = min(ans, Dis(a[v[x].r + i], a[v[y].r + j]));
        }
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
