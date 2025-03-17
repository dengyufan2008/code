#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 3e5 + 1, kMaxM = kMaxN << 1, kMod = 1e9 + 7;
struct E {
  int x, l, r;
} e[kMaxN];
struct Q {
  int x, y, o;
  int w;   // 区间内非前缀最大值的最大值
  int c;   // 区间内不超过 w 的数的个数
  int mx;  // 区间最大值
  bool b;  // 是否合法
} q[kMaxN];
int n, m, a[kMaxN], p[kMaxN];
LL fact[kMaxM], _fact[kMaxM];
vector<int> l;

class Bit {
  int d[kMaxN];

 public:
  void Add(int x) {
    for (int i = x; i <= n; i += i & -i) {
      d[i]++;
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
} bit;

class Seg {
  int v[kMaxN << 2];

  void Pushdown(int p) {
    if (v[p]) {
      v[p << 1] = v[p << 1 | 1] = v[p], v[p] = 0;
    }
  }

  void Change(int p, int l, int r, int _l, int _r, int x) {
    if (l >= _l && r <= _r) {
      v[p] = x;
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Change(p << 1, l, mid, _l, _r, x);
    }
    if (mid < _r) {
      Change(p << 1 | 1, mid + 1, r, _l, _r, x);
    }
  }

  int Ask(int p, int l, int r, int x) {
    if (l == r) {
      return v[p];
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      return Ask(p << 1, l, mid, x);
    } else {
      return Ask(p << 1 | 1, mid + 1, r, x);
    }
  }

 public:
  void Change(int l, int r, int x) { Change(1, 1, n, l, r, x); }
  int Ask(int x) { return Ask(1, 1, n, x); }
} seg;

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxM; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxM - 1] = Pow(fact[kMaxM - 1]);
  for (int i = kMaxM - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], p[a[i]] = i;
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> q[i].x >> q[i].y, q[i].o = i;
  }
  for (int i = 1; i <= n; i++) {
    for (; !l.empty() && a[l.back()] < a[i]; l.pop_back()) {
    }
    e[i].l = l.empty() ? 0 : l.back();
    l.push_back(i);
  }
  l.clear();
  for (int i = n; i >= 1; i--) {
    for (; !l.empty() && a[l.back()] > a[i]; l.pop_back()) {
    }
    e[i].r = l.empty() ? n + 1 : l.back();
    l.push_back(i);
  }
  l.clear();
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.y < j.y;
  });
  for (int i = 1, j = 1; i <= n; i++) {
    e[i].x = i, e[i].l ? seg.Change(1, e[i].l, a[i]) : void();
    for (; j <= m && q[j].y == i; j++) {
      q[j].w = seg.Ask(q[j].x);
    }
  }
  for (int i = 1, j = 1; i <= n; i++) {
    seg.Change(e[i].l + 1, i, a[i]);
    for (; j <= m && q[j].y == i; j++) {
      q[j].mx = seg.Ask(q[j].x);
    }
  }
  sort(e + 1, e + n + 1, [](E i, E j) {
    return i.r < j.r;
  });
  for (int i = 1, j = 1, k = 1, mx = 0; i <= n; i++) {
    for (; j <= n && e[j].r == i; j++) {
      mx = max(mx, e[j].l);
    }
    for (; k <= m && q[k].y == i; k++) {
      q[k].b = q[k].x > mx;
    }
  }
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.w < j.w;
  });
  for (int i = 0, j = 1; i <= n; i++) {
    i ? bit.Add(p[i]) : void();
    for (; j <= m && q[j].w == i; j++) {
      q[j].c = bit.Ask(q[j].x, q[j].y);
    }
  }
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.o < j.o;
  });
  for (int i = 1; i <= m; i++) {
    if (!q[i].b || q[i].c < q[i].w) {
      cout << 0 << '\n';
    } else {
      int x = n - q[i].y + q[i].x - 1;
      int y = q[i].mx - q[i].y + q[i].x - 1;
      LL ans = C(x * 2 - y, x) - C(x * 2 - y, x + 1);
      cout << (ans + kMod) % kMod << '\n';
    }
  }
  return 0;
}
