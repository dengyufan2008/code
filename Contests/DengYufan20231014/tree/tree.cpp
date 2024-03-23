#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("tree.in");
ofstream cout("tree.out");

const LL kMaxN = 1e6 + 2;
struct V {
  LL l, s, d, *f;
  vector<LL> e;
} v[kMaxN];
LL t, n, *h, a[kMaxN], ans[kMaxN], w[kMaxN * 10];

void Add(LL l, LL r, LL x) { ans[l] += x, ans[r + 1] -= x; }

void S(LL x) {
  v[x].l = v[x].s = 1;
  for (LL &i : v[x].e) {
    v[i].d = v[x].d + 1, S(i);
    v[x].l = max(v[x].l, v[i].l + 1), v[x].s += v[i].s;
    if (v[i].l > v[v[x].e[0]].l) {
      swap(i, v[x].e[0]);
    }
  }
}

void T(LL x, bool b) {
  if (b) {
    v[x].f = h, h += v[x].l;
  }
  Add(0, v[x].d, a[v[x].s]), v[x].f[0] = v[x].s;
  if (!v[x].e.empty()) {
    v[v[x].e[0]].f = v[x].f + 1, T(v[x].e[0], 0);
  }
  for (LL i = 1, p; i < v[x].e.size(); i++) {
    p = v[x].e[i], T(p, 1);
    for (LL j = 0; j < v[p].l; j++) {
      Add(j + 1, v[x].d + j + 1, a[v[x].f[j + 1] + v[p].f[j]] - a[v[x].f[j + 1]] - a[v[p].f[j]]);
      v[x].f[j + 1] += v[p].f[j];
    }
  }
  Add(v[x].l, n - 1, a[0]);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    h = w;
    for (LL i = 0; i <= n; i++) {
      v[i].e.clear(), ans[i] = 0;
    }
    cin >> n;
    for (LL i = 2, x; i <= n; i++) {
      cin >> x;
      v[x].e.push_back(i);
    }
    for (LL i = 0; i <= n; i++) {
      cin >> a[i];
    }
    S(1), T(1, 1);
    for (LL i = 1; i < n; i++) {
      ans[i] += ans[i - 1];
    }
    for (LL i = 0; i < n; i++) {
      cout << ans[i] << ' ';
    }
    cout << '\n';
  }
  return 0;
}
