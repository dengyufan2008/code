#include <algorithm>
#include <chrono>
#include <fstream>
#include <map>
#include <random>
#include <set>
#include <vector>
#define LL unsigned long long

using namespace std;

ifstream cin("over.in");
ofstream cout("over.out");

const int kMaxN = 1e1 + 1, kMaxL = 18;  // CHICK
struct V {
  int v, _v, d, r, s, f[kMaxL];
  LL w, _w;
  vector<int> e;
} v[kMaxN];
struct P {
  int o, x, y;
  LL l, r;
  int z;
} p[kMaxN];
struct Q {
  int o, x, y, z;
  LL d;
} q[kMaxN * 6];
struct E {
  LL n, d[2][kMaxN];

  void Clear() {
    for (int i = 1; i <= n; i++) {
      d[i][0] = d[i][1] = 0;
    }
  }

  void Xor0(int x, LL y) {
    for (int i = x; i <= n; i += i & -i) {
      d[0][i] ^= y;
    }
  }

  void Xor1(int x, LL y) {
    for (int i = x; i <= n; i += i & -i) {
      d[1][i] ^= y;
    }
  }

  void Xor(int x, int y, LL z) { x & 1 ? Xor1(x + 1 >> 1, z) : Xor0(x + 1 >> 1, z), y + 1 & 1 ? Xor1(y + 2 >> 1, z) : Xor0(y + 2 >> 1, z); }

  LL Ask0(int x) {
    LL ans = 0;
    for (int i = x; i >= 1; i -= i & -i) {
      ans ^= d[0][i];
    }
    return ans;
  }

  LL Ask1(int x) {
    LL ans = 0;
    for (int i = x; i >= 1; i -= i & -i) {
      ans ^= d[1][i];
    }
    return ans;
  }

  LL Ask(int x, int y) { return (x - 1 & 1 ? Ask1(x >> 1) : Ask0(x >> 1)) ^ (y & 1 ? Ask1(y + 1 >> 1) : Ask0(y + 1 >> 1)); }
} e;
int n, m, _v, _q;
LL ans[kMaxN];
set<int> s[kMaxN];
map<LL, int> h;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());  // CHICK

void T(int f, int x) {
  v[x].d = v[f].d + 1, v[x].r = ++_v, v[x].s = 1, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i);
      v[x].s += v[i].s;
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

void AddChange(int v, int x, int y, LL w) {
  _q++, q[_q] = {_q, x, v, v, w};
  _q++, q[_q] = {_q, y, v, v, w};
}

void AddQuery(int r, int x, int y, LL d) {
  _q++, q[_q] = {-_q, r, x, y, d};
}

void Divide(int l, int r) {
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Divide(l, mid), Divide(mid + 1, r);
  sort(q + l, q + r + 1, [](Q i, Q j) { return i.x < j.x || i.x == j.x && i.o > j.o; });
  for (int o = 1; o >= 0; o--) {
    for (int i = l, j; i <= r; i = j) {
      for (j = i; j <= r && q[i].x == q[j].x; j++) {
        if (q[j].o > 0 && q[j].o <= mid) {
          e.Xor(q[j].y, q[j].z, q[j].d);
        } else if (o && q[j].o < 0 && -q[j].o > mid) {
          ans[q[j].d] ^= e.Ask(q[j].y, q[j].z);
        }
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    cin >> v[i].v;
    v[i]._v = v[i].v, s[v[i].v].insert(i);
  }
  T(0, 1), e.n = n;
  for (int i = 1; i <= n; i++) {
    LL c = 0;
    for (int j : s[i]) {
      LL w = Rand();
      c ^= w, v[j].w = v[j]._w = w, e.Xor(v[j].r, v[j].r + v[j].s, w);
    }
    if (!s[i].empty()) {
      int x = *s[i].begin();
      v[x].w ^= c, v[x]._w ^= c, e.Xor(v[x].r, v[x].r + v[x].s, c);
    }
  }
  for (int i = 1, o, x, y, l, r, z; i <= m; i++) {
    cin >> o >> x >> y;
    if (o == 1) {
      int _x = *s[v[x].v].begin() == x ? *--s[v[x].v].end() : *s[v[x].v].begin();
      int _y = s[y].empty() ? x : *s[y].begin();
      LL w = v[x].w, _w = Rand();
      s[v[x].v].erase(x), s[y].insert(x), v[x].v = y, p[i] = {o, x, y, w, _w};

      AddChange(v[x].v, v[x].r, v[x].r + v[x].s, w ^ _w);
      v[x].w ^= w ^ _w;

      AddChange(v[_x].v, v[_x].r, v[_x].r + v[_x].s, x == _x ? 0 : w);
      v[_x].w ^= x == _x ? 0 : w;

      AddChange(v[_y].v, v[_y].r, v[_y].r + v[_y].s, _w);
      v[_y].w ^= _w;

    } else {
      cin >> l >> r >> z;
      int lca = Lca(x, y);
      p[i] = {o, x, y, (LL)l, (LL)r, z};
      ans[i] ^= e.Ask(v[x].r, v[x].r);
      ans[i] ^= e.Ask(v[y].r, v[y].r);
      ans[i] ^= e.Ask(v[lca].r, v[lca].r);
      ans[i] ^= e.Ask(v[v[lca].f[0]].r, v[v[lca].f[0]].r);
      AddQuery(v[x].r, l, r, i), AddQuery(v[y].r, l, r, i);
      AddQuery(v[lca].r, l, r, i), AddQuery(v[v[lca].f[0]].r, l, r, i);
    }
  }
  e.Clear(), Divide(1, _q);
  for (int i = 1; i <= n; i++) {
    s[i].clear();
  }
  for (int i = 1; i <= n; i++) {
    v[i].v = v[i]._v, s[v[i].v].insert(i), h[v[i].w] = v[i].v;
  }
  for (int i = 1, o, x, y, l, r, z; i <= m; i++) {
    o = p[i].o, x = p[i].x, y = p[i].y, l = p[i].l, r = p[i].r, z = p[i].z;
    if (o == 1) {
      int _x = *s[v[x].v].begin() == x ? *--s[v[x].v].end() : *s[v[x].v].begin();
      int _y = s[y].empty() ? x : *s[y].begin();
      LL w = v[x].w, _w = Rand();
      v[x].v = y, p[i] = {o, x, y, w, _w};
      v[x].w ^= w ^ _w;
      v[_x].w ^= x == _x ? 0 : w;
      v[_y].w ^= _w;
    } else if (z == 0) {
      cout << (ans[i] ? "No\n" : "Yes\n");
    } else if (z == 1) {
      cout << (h.count(ans[i]) && h[ans[i]] >= l && h[ans[i]] <= r ? "Yes\n" : "No\n");
    }
  }
  return 0;
}
