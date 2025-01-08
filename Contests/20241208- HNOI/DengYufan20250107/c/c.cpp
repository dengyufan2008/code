#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e5 * 2 + 2;
struct A {
  int x, l, r;
  bool o;  // 0:insert 1:delete
} a[kMaxN];
struct E {
  int l, r, c, d;
};
int t, n, m, k, dx[kMaxN], dy[kMaxN];
vector<E> e;

class Seg {  // range: [2, m]
  struct W {
    int xl, l, xr, r;
  };
  struct V {
    int mn;         // 覆盖次数的最小值
    int c;          // 最小值的出现次数 (离散化前)
    int x;          // 最小值中左端点是否都一致, 一致则为左端点的值, 否则为 0
    int l, r, ans;  // 左/右边的最小值连续段长度, 内部最小值连续段长度的最大值 (离散化前)

    int t1;  // 将区间内覆盖次数加上
    int t2;  // 将区间内的最小值的左端点赋值
  } v[kMaxN << 2];

  void Tag1(int p, int w) { v[p].mn += w, v[p].t1 += w; }
  void Tag2(int p, int x) { v[p].x = v[p].t2 = x; }

  void Pushdown(int p) {
    if (v[p].t1) {
      Tag1(p << 1, v[p].t1), Tag1(p << 1 | 1, v[p].t1);
      v[p].t1 = 0;
    }
    if (v[p].t2) {
      if (v[p << 1].mn == v[p].mn) {
        Tag2(p << 1, v[p].t2);
      }
      if (v[p << 1 | 1].mn == v[p].mn) {
        Tag2(p << 1 | 1, v[p].t2);
      }
      v[p].t2 = 0;
    }
  }

  W Merge(W w1, W w2, int l, int r, int x) {
    static W w;
    int mid = l + r >> 1;
    w.xl = w1.xl, w.xr = w2.xr;
    w.l = w1.l == dy[mid + 1] - dy[l] && w1.xl == w2.xl ? w1.l + w2.l : w1.l;
    w.r = w2.r == dy[r + 1] - dy[mid + 1] && w2.xr == w1.xr ? w2.r + w1.r : w2.r;
    bool o1 = w1.xl != w1.xr || w1.l + w1.r < dy[mid + 1] - dy[l];
    bool o2 = w2.xl != w2.xr || w2.l + w2.r < dy[r + 1] - dy[mid + 1];
    if (w1.xr != w2.xl) {
      if (w1.r && o1) {
        e.push_back({w1.xr, x, w1.r, w1.r});
      }
      if (w2.l && o2) {
        e.push_back({w2.xl, x, w2.l, w2.l});
      }
    } else {
      if (w1.r + w2.l && o1 && o2) {
        e.push_back({w1.xr, x, w1.r + w2.l, w1.r + w2.l});
      }
    }
    return w;
  }

  V Merge(V x, V y, int l, int r) {
    static V z;
    int mid = l + r >> 1;
    if (x.mn < y.mn) {
      z.mn = x.mn, z.c = x.c, z.x = x.x;
      z.l = x.l, z.r = 0, z.ans = x.ans;
    } else if (x.mn > y.mn) {
      z.mn = y.mn, z.c = y.c, z.x = y.x;
      z.l = 0, z.r = y.r, z.ans = y.ans;
    } else {
      z.mn = x.mn, z.c = x.c + y.c;
      z.x = x.x == y.x ? x.x : 0;
      z.l = x.l == dy[mid + 1] - dy[l] ? x.l + y.l : x.l;
      z.r = y.r == dy[r + 1] - dy[mid + 1] ? y.r + x.r : y.r;
      z.ans = max(max(x.ans, y.ans), x.r + y.l);
    }
    return z;
  }

  void Init(int p, int l, int r) {
    int len = dy[r + 1] - dy[l];
    v[p] = {0, len, 1, len, len, len, 0, 0};
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
  }

  void Add(int p, int l, int r, int _l, int _r, int w) {
    if (l >= _l && r <= _r) {
      return Tag1(p, w);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, w);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, w);
    }
    v[p] = Merge(v[p << 1], v[p << 1 | 1], l, r);
  }

  void Change(int p, int l, int r, int _l, int _r, int x) {
    if (v[p].mn > 0) {
      return;
    } else if (l >= _l && r <= _r) {
      return Tag2(p, x);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Change(p << 1, l, mid, _l, _r, x);
    }
    if (mid < _r) {
      Change(p << 1 | 1, mid + 1, r, _l, _r, x);
    }
    v[p] = Merge(v[p << 1], v[p << 1 | 1], l, r);
  }

  W Calc(int p, int l, int r, int x) {
    if (v[p].mn > 0) {
      return {1, 0, 1, 0};
    } else if (v[p].x) {
      if (v[p].c > v[p].l + v[p].r) {
        e.push_back({v[p].x, x, v[p].c - v[p].l - v[p].r, v[p].ans});
      }
      return {v[p].l ? v[p].x : 1, v[p].l, v[p].r ? v[p].x : 1, v[p].r};
    }
    Pushdown(p);
    int mid = l + r >> 1;
    W w1 = Calc(p << 1, l, mid, x);
    W w2 = Calc(p << 1 | 1, mid + 1, r, x);
    return Merge(w1, w2, l, r, x);
  }

  W Calc(int p, int l, int r, int _l, int _r, int x) {
    if (v[p].mn > 0) {
      return {1, 0, 1, 0};
    } else if (l >= _l && r <= _r) {
      return Calc(p, l, r, x);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    W w1 = {1, 0, 1, 0}, w2 = {1, 0, 1, 0};
    if (mid >= _l) {
      w1 = Calc(p << 1, l, mid, _l, _r, x);
    }
    if (mid < _r) {
      w2 = Calc(p << 1 | 1, mid + 1, r, _l, _r, x);
    }
    return Merge(w1, w2, l, r, x);
  }

 public:
  void Init() { Init(1, 2, m); }
  void Add(int l, int r, int w) { Add(1, 2, m, l, r, w); }
  // 将区间内没有被覆盖的位置的左端点赋为 x
  void Change(int l, int r, int x) { Change(1, 2, m, l, r, x); }
  // 更新 e, 并将区间内没有被覆盖的位置的左端点置 1 (为保证复杂度)
  void Calc(int l, int r, int x) {
    W w = Calc(1, 2, m, l, r, x);
    if (w.l) {
      e.push_back({w.xl, x, w.l, w.l});
    }
    if (w.r) {
      e.push_back({w.xr, x, w.r, w.r});
    }
    Change(l, r, 1);
  }
} seg;

void Input() {
  static int ox[kMaxN], oy[kMaxN], ansx[kMaxN], ansy[kMaxN];
  cin >> k, k = k << 1 | 1;
  for (int i = 2; i <= k; i++) {
    cin >> dx[i] >> dy[i], ox[i] = oy[i] = i;
    (i & 1) && (dx[i]++, dy[i]++);
  }
  sort(ox + 2, ox + k + 1, [](int i, int j) {
    return dx[i] < dx[j];
  });
  sort(oy + 2, oy + k + 1, [](int i, int j) {
    return dy[i] < dy[j];
  });
  ansx[ox[2]] = 2, ansy[oy[2]] = 2;
  for (int i = 3; i <= k; i++) {
    ansx[ox[i]] = ansx[ox[i - 1]] + (dx[ox[i]] > dx[ox[i - 1]]);
    ansy[oy[i]] = ansy[oy[i - 1]] + (dy[oy[i]] > dy[oy[i - 1]]);
  }
  for (int i = 2; i <= k; i++) {
    a[i] = {ansx[i], ansy[i ^ (i & 1)], ansy[i ^ (i & 1) ^ 1], bool(i & 1)};
  }
  n = ansx[ox[k]], m = ansy[oy[k]];
  sort(dx + 2, dx + k + 1), unique(dx + 2, dx + k + 1);
  sort(dy + 2, dy + k + 1), unique(dy + 2, dy + k + 1);
}

void Calc() {
  static vector<int> l;
  static vector<pair<int, bool>> b;
  static vector<pair<int, int>> v;
  sort(a + 2, a + k + 1, [](A i, A j) {
    return i.x < j.x || i.x == j.x && i.o < j.o;
  });
  e.clear(), seg.Init();
  for (int x = 2, i = 2; x <= n; x++) {
    for (bool o : {0, 1}) {
      b.clear();
      for (; i <= k && a[i].x == x && a[i].o == o; i++) {
        b.push_back({a[i].l, 0}), b.push_back({a[i].r, 1});
      }
      sort(b.begin(), b.end()), v.clear();
      for (int j = 0, k = 0; j < b.size(); j++) {
        int u = 0;
        for (; k < b.size() && b[j].first == b[k].first; k++) {
          u += b[k].second ? -1 : 1;
        }
        if (u > 0) {
          while (u--) {
            l.push_back(b[j].first);
          }
        } else if (u < 0) {
          while (u++) {
            v.push_back({l.back(), b[j].first});
            l.pop_back();
          }
        }
      }
      if (o) {  // delete
        for (auto j : v) {
          seg.Add(j.first, j.second - 1, -1);
          seg.Calc(j.first, j.second - 1, x);
        }
      } else {  // insert
        for (auto j : v) {
          seg.Change(j.first, j.second - 1, x);
          seg.Add(j.first, j.second - 1, 1);
        }
      }
    }
  }
}

void Print() {
  int ans = 0;
  sort(e.begin(), e.end(), [](E i, E j) {
    return i.l < j.l || i.l == j.l && i.r < j.r;
  });
  for (int i = 0, j = 0; i < e.size(); i = j) {
    for (; j < e.size() && e[i].l == e[j].l && e[i].r == e[j].r; j++) {
    }
    ans++;
  }
  cout << ans << '\n';
  for (int i = 0, j = 0; i < e.size(); i = j) {
    int c = 0, d = 0;
    for (; j < e.size() && e[i].l == e[j].l && e[i].r == e[j].r; j++) {
      c += e[j].c, d = max(d, e[j].d);
    }
    cout << dx[e[i].l] << ' ' << dx[e[i].r] - 1 << ' ' << c << ' ' << d << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    Input(), Calc(), Print();
  }
  return 0;
}
