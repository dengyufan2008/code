#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("n.in");
ofstream cout("n.out");

const int kMaxN = 2e5 + 2;
struct A {
  int l, r;
} a[kMaxN];
struct V {
  int f, g, ans;
} v[kMaxN << 2];
int n, m, k, s[kMaxN], f[kMaxN], g[kMaxN], ans[kMaxN];

V Merge(V x, V y) {
  return {max(x.f, y.f), max(x.g, y.g), max(max(x.ans, y.ans), x.f + y.g)};
}

void Init(int p, int l, int r) {
  if (l == r) {
    v[p].f = f[l], v[p].g = g[l], v[p].ans = f[l] + g[l];
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
  v[p] = Merge(v[p << 1], v[p << 1 | 1]);
}

V Max(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return v[p];
  }
  int mid = l + r >> 1;
  if (mid >= _l && mid < _r) {
    V x = Max(p << 1, l, mid, _l, _r);
    V y = Max(p << 1 | 1, mid + 1, r, _l, _r);
    return Merge(x, y);
  } else if (mid >= _l) {
    return Max(p << 1, l, mid, _l, _r);
  } else {
    return Max(p << 1 | 1, mid + 1, r, _l, _r);
  }
}

int GetRoot(int x) {
  return s[x] == x ? x : s[x] = GetRoot(s[x]);
}

void Input() {
  cin >> n, k = n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].l >> a[i].r, m = max(m, a[i].r);
  }
  sort(a + 1, a + n + 1, [](A i, A j) {
    return i.r < j.r || i.r == j.r && i.l < j.l;
  });
  for (int i = 1; i <= m + 1; i++) {
    s[i] = i;
  }
  for (int i = 1; i <= n; i++) {
    a[i].l = GetRoot(a[i].l);
    if (a[i].l <= a[i].r) {
      s[a[i].l] = GetRoot(a[i].l + 1);
    }
  }
  for (int i = 1, j = 0; i <= n; i++) {
    if (a[i].l <= a[i].r) {
      swap(a[i], a[++j]);
    }
  }
  for (; n >= 1 && a[n].l > a[n].r; n--) {
  }
}

void CalcFG() {
  for (int i = 1; i <= n; i++) {
    if (a[i].r < m) {
      f[a[i].r + 1]++;
    }
    if (a[i].l > 1) {
      g[a[i].l - 1]++;
    }
  }
  for (int i = 1; i <= m; i++) {
    f[i] += f[i - 1];
  }
  for (int i = m; i >= 1; i--) {
    g[i] += g[i + 1];
  }
  for (int i = 1; i <= m; i++) {
    f[i] -= i, g[i] += i;
  }
}

void CalcAns() {
  Init(1, 1, m);
  for (int i = 1, j = 1; i <= m; i++) {
    for (j = max(j, i); j <= m && Max(1, 1, m, i, j).ans < n; j++) {
    }
    ans[j - i]++;
  }
  for (int i = m; i >= 1; i--) {
    ans[i] += ans[i + 1];
  }
  for (int i = 1; i <= k; i++) {
    cout << ans[i] << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), CalcFG(), CalcAns();
  return 0;
}
