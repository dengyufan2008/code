#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const LL kMaxN = 25e4 + 1, kInf = 1e18;
struct E {
  LL v, x;
  vector<pair<LL, LL>> e;
} e[kMaxN];
struct V {
  LL p, d, f[18], g[18];
  vector<pair<LL, LL>> e;
} v[kMaxN];
LL n, m, k, t, h, a[kMaxN], q[kMaxN];
bool b[kMaxN];

void Update(LL s, LL x) {
  if (e[s].x != x) {
    e[s].e.clear(), e[s].x = x;
  }
}

void S(LL f, LL x) {
  v[x].p = ++t, v[x].d = v[f].d + 1, v[x].f[0] = f;
  for (auto i : v[x].e) {
    if (i.first != f) {
      v[i.first].g[0] = i.second;
      S(x, i.first);
    }
  }
}

void T(LL x) {
  e[x].v = 0;
  for (auto i : e[x].e) {
    T(i.first);
    if (b[i.first]) {
      e[x].v += i.second;
    } else {
      e[x].v += min(e[i.first].v, i.second);
    }
  }
}

pair<LL, LL> Lca(LL x, LL y) {
  LL ans = kInf;
  if (v[x].d < v[y].d) {
    swap(x, y);
  }
  for (LL i = 17; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      ans = min(ans, v[x].g[i]);
      x = v[x].f[i];
    }
  }
  for (LL i = 17; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      ans = min(ans, min(v[x].g[i], v[y].g[i]));
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return {x == y ? x : v[x].f[0], x == y ? ans : min(ans, min(v[x].g[0], v[y].g[0]))};
}

void Build(LL x) {
  q[h = 1] = 1, sort(a + 1, a + k + 1, [](LL i, LL j) { return v[i].p < v[j].p; });
  for (LL i = 1; i <= k; i++) {
    LL c = Lca(q[h], a[i]).first;
    if (c != q[h]) {
      while (v[q[h - 1]].p > v[c].p) {
        Update(q[h - 1], x), e[q[h - 1]].e.push_back({q[h], Lca(q[h], q[h - 1]).second}), h--;
      }
      Update(c, x), e[c].e.push_back({q[h], Lca(q[h], c).second}), h--;
      if (v[q[h]].p != v[c].p) {
        q[++h] = c;
      }
    }
    q[++h] = a[i];
  }
  for (LL i = 1; i < h; i++) {
    Update(q[i], x), e[q[i]].e.push_back({q[i + 1], Lca(q[i + 1], q[i]).second});
  }
}

int main() {
  cin >> n;
  fill(&v[0].g[0], &v[0].g[18], kInf), fill(&v[1], &v[kMaxN], v[0]);
  for (LL i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  S(0, 1);
  for (LL i = 1; i <= 17; i++) {
    for (LL j = 1; j <= n; j++) {
      v[j].f[i] = v[v[j].f[i - 1]].f[i - 1];
      v[j].g[i] = min(v[j].g[i - 1], v[v[j].f[i - 1]].g[i - 1]);
    }
  }
  cin >> m;
  for (LL i = 1; i <= m; i++) {
    cin >> k;
    for (LL j = 1; j <= k; j++) {
      cin >> a[j];
      b[a[j]] = 1;
    }
    Build(i), T(1);
    cout << e[1].v << '\n';
    for (LL j = 1; j <= k; j++) {
      b[a[j]] = 0;
    }
  }
  return 0;
}
