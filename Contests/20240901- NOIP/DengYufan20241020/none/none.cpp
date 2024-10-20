#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("none.in");
ofstream cout("none.out");

const int kMaxN = 3e5 + 1, kMaxL = 19;
struct V {
  int d, r, s, f[kMaxL];
  vector<int> e;
} v[kMaxN];
struct E {
  int x, l, r, o;
};
struct D {
  int w, t;
} d[kMaxN << 2];
int n;
long long ans;
vector<E> e;

void T(int f, int x) {
  static int k = 0;
  v[x].d = v[f].d + 1, v[x].r = ++k, v[x].s = 1, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i), v[x].s += v[i].s;
    }
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

void Add(int p, int l, int r, int _l, int _r, int t) {
  if (l >= _l && r <= _r) {
    d[p].t += t;
    if (d[p].t) {
      d[p].w = r - l + 1;
    } else {
      d[p].w = l == r ? 0 : d[p << 1].w + d[p << 1 | 1].w;
    }
    return;
  }
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(p << 1, l, mid, _l, _r, t);
  }
  if (mid < _r) {
    Add(p << 1 | 1, mid + 1, r, _l, _r, t);
  }
  if (!d[p].t) {
    d[p].w = d[p << 1].w + d[p << 1 | 1].w;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, 1);
  for (int i = 1; i < n; i++) {
    int x = i, y = i + 1;
    v[x].d < v[y].d ? swap(x, y) : void();
    if (v[y].r <= v[x].r && v[y].r + v[y].s > v[x].r) {
      int z = F(x, v[x].d - v[y].d - 1);
      e.push_back({1, v[x].r, v[x].r + v[x].s - 1, 1});
      e.push_back({v[z].r, v[x].r, v[x].r + v[x].s - 1, -1});
      e.push_back({v[z].r + v[z].s, v[x].r, v[x].r + v[x].s - 1, 1});
      e.push_back({v[x].r, 1, v[z].r - 1, 1});
      e.push_back({v[x].r + v[x].s, 1, v[z].r - 1, -1});
      e.push_back({v[x].r, v[z].r + v[z].s, n, 1});
      e.push_back({v[x].r + v[x].s, v[z].r + v[z].s, n, -1});
    } else {
      e.push_back({v[x].r, v[y].r, v[y].r + v[y].s - 1, 1});
      e.push_back({v[x].r + v[x].s, v[y].r, v[y].r + v[y].s - 1, -1});
      e.push_back({v[y].r, v[x].r, v[x].r + v[x].s - 1, 1});
      e.push_back({v[y].r + v[y].s, v[x].r, v[x].r + v[x].s - 1, -1});
    }
  }
  sort(e.begin(), e.end(), [](E i, E j) {
    return i.x < j.x;
  });
  for (int i = 1, j = 0; i <= n; i++) {
    for (; j < e.size() && e[j].x == i; j++) {
      if (e[j].l <= e[j].r) {
        Add(1, 1, n, e[j].l, e[j].r, e[j].o);
      }
    }
    ans += d[1].w;
  }
  cout << (1LL * n * (n + 1) - ans >> 1) << '\n';
  return 0;
}
