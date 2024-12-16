// [solution](https://qoj.ac/blog/jiangly/blog/958)
#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const LL kMaxN = 2e5 + 1, kInf = 1e18;
struct A {
  int x, y, o;
} a[kMaxN];
struct F {
  LL d[4] = {kInf, kInf, kInf, kInf};  // 0/2: A 是否选过了, 0/1: B 是否选过了
} f;
struct T {
  LL d[2];  // 0/1: 是否选过了
  bool o;   // 是否需要反转状态
};
struct V {
  F f;
  T w, t;
} v[kMaxN << 2];
int n;

F MergeFF(F x, F y) {
  return {min(x.d[0], y.d[0]), min(x.d[1], y.d[1]),
          min(x.d[2], y.d[2]), min(x.d[3], y.d[3])};
}

// 2: Merge A, 1: Merge B
F MergeFT(F x, T y, int o) {
  x.d[o ^ 3] += y.d[0], x.d[0] += y.d[0];
  x.d[o] += y.d[1], x.d[3] += y.d[1];
  if (y.o) {
    swap(x.d[o ^ 3], x.d[3]);
    swap(x.d[o], x.d[0]);
  }
  return x;
}

T MergeTT(T x, T y) {
  if (x.o) {
    swap(y.d[0], y.d[1]);
  }
  x.d[0] += y.d[0], x.d[1] += y.d[1], x.o ^= y.o;
  return x;
}

void Pushdown(int p) {
  v[p << 1].f = MergeFT(v[p << 1].f, v[p].t, 2);
  v[p << 1].t = MergeTT(v[p << 1].t, v[p].t);
  v[p << 1 | 1].f = MergeFT(v[p << 1 | 1].f, v[p].t, 2);
  v[p << 1 | 1].t = MergeTT(v[p << 1 | 1].t, v[p].t);
  v[p].t = T();
}

void Pushup(int p) {
  v[p].f = MergeFF(MergeFT(v[p << 1 | 1].f, v[p << 1].w, 1), v[p << 1].f);
  v[p].w = MergeTT(v[p << 1 | 1].w, v[p << 1].w);
}

void ChangeF(int p, int l, int r, int x, F f) {
  if (l == r) {
    v[p].f = f;
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= x) {
    ChangeF(p << 1, l, mid, x, f);
  } else {
    ChangeF(p << 1 | 1, mid + 1, r, x, f);
  }
  Pushup(p);
}

void ChangeW(int p, int l, int r, int x, int w) {
  if (l == r) {
    v[p].w.d[0] = w, v[p].w.o = 1;
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= x) {
    ChangeW(p << 1, l, mid, x, w);
  } else {
    ChangeW(p << 1 | 1, mid + 1, r, x, w);
  }
  Pushup(p);
}

void Tag(int p, int l, int r, int x, int t) {
  if (r <= x) {
    v[p].f = MergeFT(v[p].f, {t, 0, 1}, 2);
    v[p].t = MergeTT(v[p].t, {t, 0, 1});
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  Tag(p << 1, l, mid, x, t);
  if (mid < x) {
    Tag(p << 1 | 1, mid + 1, r, x, t);
  }
  Pushup(p);
}

pair<F, T> Ask(int p, int l, int r, int x) {
  if (l >= x) {
    return {v[p].f, v[p].w};
  }
  Pushdown(p);
  int mid = l + r >> 1;
  auto ans = Ask(p << 1 | 1, mid + 1, r, x);
  if (mid >= x) {
    auto u = Ask(p << 1, l, mid, x);
    ans.first = MergeFF(MergeFT(ans.first, u.second, 1), u.first);
    ans.second = MergeTT(ans.second, u.second);
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x;
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i].y;
  }
  sort(a + 1, a + n + 1, [](A i, A j) {
    return i.y < j.y;
  });
  for (int i = 1; i <= n; i++) {
    a[i].o = i;
  }
  sort(a + 1, a + n + 1, [](A i, A j) {
    return i.x > j.x || i.x == j.x && i.o > j.o;
  });
  f = {0, kInf, kInf, kInf}, ChangeF(1, 1, n + 1, n + 1, f);
  for (int i = 1; i <= n; i++) {
    f = Ask(1, 1, n + 1, a[i].o).first;  // 后缀
    f = MergeFT(f, {a[i].x, 0, 1}, 2);   // 折线上的也认为是 A 点
    Tag(1, 1, n + 1, a[i].o, a[i].x);    // 前缀
    ChangeF(1, 1, n + 1, a[i].o, f);
    ChangeW(1, 1, n + 1, a[i].o, a[i].y);
  }
  f = Ask(1, 1, n + 1, 1).first;
  cout << min(min(f.d[0], f.d[1]), min(f.d[2], f.d[3])) << '\n';
  return 0;
}
