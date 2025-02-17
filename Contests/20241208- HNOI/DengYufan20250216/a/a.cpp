#include <algorithm>
#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

const LL kMaxN = 3e4 + 1, kW = 1e6, kV = 1e11;
struct E {
  int l, r;
  LL w, _w;
} e[kMaxN];
int n, m;
LL a[kMaxN], _a[kMaxN], f[kMaxN];

class Seg {
  struct V {
    LL w;         // 区间最小值
    LL t1;        // 加法标记
    LL t2 = -kV;  // 覆盖标记
  } v[kMaxN << 2];

  void Tag1(int p, LL t) {
    v[p].w += t, v[p].t1 += t;
    if (v[p].t2 != -kV) {
      v[p].t2 += t;
    }
  }

  void Tag2(int p, LL t) {
    v[p].w = t, v[p].t1 = 0, v[p].t2 = t;
  }

  void Pushdown(int p) {
    if (v[p].t1) {
      Tag1(p << 1, v[p].t1);
      Tag1(p << 1 | 1, v[p].t1);
      v[p].t1 = 0;
    }
    if (v[p].t2 != -kV) {
      Tag2(p << 1, v[p].t2);
      Tag2(p << 1 | 1, v[p].t2);
      v[p].t2 = -kV;
    }
  }

  void Init(int p, int l, int r) {
    v[p] = v[0];
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
  }

  void Add(int p, int l, int r, int x, LL w) {
    if (l >= x) {
      return Tag1(p, w);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    Add(p << 1 | 1, mid + 1, r, x, w);
    if (mid >= x) {
      Add(p << 1, l, mid, x, w);
    }
    v[p].w = min(v[p << 1].w, v[p << 1 | 1].w);
  }

  LL Ask(int p, int l, int r, int x) {
    if (l == r) {
      return v[p].w;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      return Ask(p << 1, l, mid, x);
    } else {
      return Ask(p << 1 | 1, mid + 1, r, x);
    }
  }

  int Find(int p, int l, int r, LL w) {
    if (l == r) {
      return l;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (v[p << 1 | 1].w < w) {
      return Find(p << 1 | 1, mid + 1, r, w);
    } else {
      return Find(p << 1, l, mid, w);
    }
  }

  void Fill(int p, int l, int r, int _l, int _r, LL w) {
    if (l >= _l && r <= _r) {
      return Tag2(p, w);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Fill(p << 1, l, mid, _l, _r, w);
    }
    if (mid < _r) {
      Fill(p << 1 | 1, mid + 1, r, _l, _r, w);
    }
    v[p].w = min(v[p << 1].w, v[p << 1 | 1].w);
  }

 public:
  void Init() { Init(1, 1, m + 1); }
  void Add(int x, LL w) { Add(1, 1, m + 1, x, w); }
  LL Ask(int x) { return Ask(1, 1, m + 1, x); }
  void Max(int x, LL w) {
    if (Ask(x) < w) {
      int y = Find(1, 1, m + 1, w);
      Fill(1, 1, m + 1, x, y, w);
    }
  }
} seg;

// 最大独立集 >= 点权和
bool Calc(LL mid) {
  LL s = 0;
  for (int i = 1; i <= n; i++) {
    e[i].w = mid - e[i]._w, s += e[i].w;
  }
  for (int i = 1; i <= m; i++) {
    a[i] = mid - _a[i], s += a[i];
  }
  seg.Init();
  for (int i = 1, j = 1; i <= m; i++) {
    for (; j <= n && e[j].l == i; j++) {
      if (e[j].w > 0) {
        seg.Add(e[j].r + 1, e[j].w);
      }
    }
    f[i] = seg.Ask(i) + a[i];
    seg.Max(i + 1, f[i]);
  }
  return seg.Ask(m + 1) >= s;
}

int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> a[1];
  for (int i = 1; i <= n; i++) {
    cin >> e[i].w, e[i].w *= kW, e[i]._w = e[i].w;
  }
  for (int i = 1; i <= m; i++) {
    cin >> a[i], a[i] *= kW, _a[i] = a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> e[i].l >> e[i].r;
  }
  sort(e + 1, e + n + 1, [](E i, E j) {
    return i.l < j.l;
  });
  LL l = 0, r = kV;
  while (l <= r) {
    LL mid = l + r >> 1;
    if (Calc(mid)) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  printf("%lld.%06lld\n", r / kW, r % kW);
  return 0;
}
