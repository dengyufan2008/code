#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

const int kMaxN = 7e4 + 1;
struct E {
  int x, l, r, o;
};
struct V {
  int w, r, s;
  vector<int> e, g;
} v[kMaxN];
struct D {
  int w, c, t, ans;
} d[kMaxN << 2];
int t, n, m, l, r;
vector<int> p[kMaxN];
vector<E> h, e[kMaxN];

void S(int f, int x) {
  v[x].r = ++m, v[x].s = 1;
  for (int i : v[x].e) {
    if (i != f) {
      S(x, i), v[x].s += v[i].s;
    }
  }
}

void A(int w, int x, int y) {
  if (x <= y) {
    e[w].push_back({x, x, y, 1});
    if (y < n) {
      e[w].push_back({y + 1, x, y, -1});
    }
  }
}

void A(int w, int x, int y, int _x, int _y) {
  A(w, x, y), A(w, _x, _y);
  if (x <= y && _x <= _y) {
    e[w].push_back({x, _x, _y, 1});
    if (y < n) {
      e[w].push_back({y + 1, _x, _y, -1});
    }
    e[w].push_back({_x, x, y, 1});
    if (_y < n) {
      e[w].push_back({_y + 1, x, y, -1});
    }
  }
}

void T(int x, int w) {
  int p = v[x].r + 1;
  for (int i = 0, j = 0; i < v[x].e.size(); i++) {
    int y = v[x].e[i];
    if (j < v[x].g.size() && v[v[x].e[i]].r + v[v[x].e[i]].s > v[v[x].g[j]].r) {
      int z = v[x].g[j];
      A(w, v[y].r, v[z].r - 1, v[z].r + v[z].s, v[y].r + v[y].s - 1), j++;
    } else {
      A(w, v[y].r, v[y].r + v[y].s - 1);
    }
  }
  for (int i : v[x].g) {
    T(i, w);
  }
}

void R() {
  for (int i = 0; i < n; i++) {
    if (p[i].empty()) {
      r = i - 1;
      break;
    } else {
      sort(p[i].begin(), p[i].end(), [](int i, int j) {
        return v[i].r < v[j].r;
      });
      int g = p[i].front();
      for (int j = 1; j < p[i].size(); j++) {
        if (v[g].r + v[g].s <= v[p[i][j]].r) {
          g = p[i].front();
        }
        v[g].g.push_back(p[i][j]), g = p[i][j];
      }
      A(i, 1, v[p[i].front()].r - 1, v[p[i].front()].r + v[p[i].front()].s, n);
      T(p[i].front(), i);
    }
  }
}

void W(int p, int l, int r) {
  d[p] = d[0], d[p].c = r - l + 1;
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  W(p << 1, l, mid), W(p << 1 | 1, mid + 1, r);
}

void G(int p, int l, int r, int o) {
  d[p].w += o, d[p].t += o;
  if (d[p].w > 0) {
    d[p].ans = r - l + 1;
  } else {
    d[p].ans = r - l + 1 - d[p].c;
  }
}

void N(int p, int l, int r) {
  int mid = l + r >> 1;
  if (d[p].t) {
    G(p << 1, l, mid, d[p].t);
    G(p << 1 | 1, mid + 1, r, d[p].t);
    d[p].t = 0;
  }
}

void U(int p, int l, int r) {
  d[p].w = min(d[p << 1].w, d[p << 1 | 1].w);
  if (d[p << 1].w < d[p << 1 | 1].w) {
    d[p].c = d[p << 1].c;
  } else if (d[p << 1].w > d[p << 1 | 1].w) {
    d[p].c = d[p << 1 | 1].c;
  } else {
    d[p].c = d[p << 1].c + d[p << 1 | 1].c;
  }
  if (d[p].w > 0) {
    d[p].ans = r - l + 1;
  } else {
    d[p].ans = r - l + 1 - d[p].c;
  }
}

void M(int p, int l, int r, int _l, int _r, int o) {
  if (l >= _l && r <= _r) {
    return G(p, l, r, o);
  }
  N(p, l, r);
  int mid = l + r >> 1;
  if (mid >= _l) {
    M(p << 1, l, mid, _l, _r, o);
  }
  if (mid < _r) {
    M(p << 1 | 1, mid + 1, r, _l, _r, o);
  }
  U(p, l, r);
}

LL C(int x) {
  LL ans = 0;
  h.clear();
  for (int i = 0; i <= x; i++) {
    h.insert(h.end(), e[i].begin(), e[i].end());
  }
  sort(h.begin(), h.end(), [](E i, E j) {
    return i.x < j.x;
  });
  h.push_back({n + 1, 0, 0, 0}), W(1, 1, n);
  for (int i = 0, j = 0; i + 1 < h.size(); i = j) {
    for (; j + 1 < h.size() && h[i].x == h[j].x; j++) {
      M(1, 1, n, h[j].l, h[j].r, h[j].o);
    }
    ans += 1LL * (n - d[1].ans) * (h[j].x - h[i].x);
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    for (int i = 0; i <= n; i++) {
      v[i].e.clear(), v[i].g.clear(), p[i].clear(), e[i].clear();
    }
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> v[i].w, p[v[i].w].push_back(i);
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    m = 0, S(0, 1), l = 0, r = n - 1, R();
    while (l <= r) {
      int mid = l + r >> 1;
      if (C(mid)) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    cout << l << ' ' << C(r) << '\n';
  }
  return 0;
}
