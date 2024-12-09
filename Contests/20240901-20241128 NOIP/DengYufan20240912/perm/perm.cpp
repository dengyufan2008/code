#include <fstream>
#define LL long long

using namespace std;

ifstream cin("perm.in");
ofstream cout("perm.out");

const int kMaxN = 5e5 + 1, kInf = 1e9;
struct V {
  int mn1, mn2, c, t;
} v[kMaxN << 2];
int n, u, a[kMaxN], o[kMaxN], f[kMaxN], g[kMaxN];
LL w, ans[kMaxN];

void Tag(int p, int t) {
  v[p].mn1 += t, v[p].mn2 += t, v[p].t += t;
}

void Pushdown(int p) {
  Tag(p << 1, v[p].t), Tag(p << 1 | 1, v[p].t), v[p].t = 0;
}

void Pushup(int p) {
  v[p].mn1 = min(v[p << 1].mn1, v[p << 1 | 1].mn1);
  v[p].mn2 = min(v[p << 1].mn2, v[p << 1 | 1].mn2);
  v[p].c = v[p << 1].c + v[p << 1 | 1].c;
}

void Init(int p, int l, int r) {
  if (l == r) {
    v[p].mn1 = g[o[l]];
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
  Pushup(p);
}

void Minus(int p, int l, int r, int _r) {
  if (r <= _r) {
    w -= v[p].c, Tag(p, -1);
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  Minus(p << 1, l, mid, _r);
  if (mid < _r) {
    Minus(p << 1 | 1, mid + 1, r, _r);
  }
  Pushup(p);
}

void Delete(int p, int l, int r, int x) {
  if (l == r) {
    w -= v[p].mn2, v[p].mn1 = kInf, v[p].mn2 = v[p].c = 0;
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= x) {
    Delete(p << 1, l, mid, x);
  } else {
    Delete(p << 1 | 1, mid + 1, r, x);
  }
  Pushup(p);
}

void Mark(int p, int l, int r) {
  if (l == r) {
    v[p].mn2 = v[p].mn1, v[p].mn1 = kInf, v[p].c = 1;
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (v[p << 1].mn1 <= 0) {
    Mark(p << 1, l, mid);
  } else {
    Mark(p << 1 | 1, mid + 1, r);
  }
  Pushup(p);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> u;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], o[a[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    static int d[kMaxN] = {};
    for (int j = a[i]; j <= n; j += j & -j) {
      f[i] += d[j];
    }
    for (int j = a[i]; j >= 1; j -= j & -j) {
      d[j]++;
    }
  }
  for (int i = n; i >= 1; i--) {
    static int d[kMaxN] = {};
    for (int j = a[i]; j <= n; j += j & -j) {
      g[i] += d[j];
    }
    for (int j = a[i]; j >= 1; j -= j & -j) {
      d[j]++;
    }
    w += min(f[i], g[i]), g[i] -= f[i];
  }
  ans[n] = w, Init(1, 1, n);
  while (v[1].mn1 <= 0) {
    Mark(1, 1, n);
  }
  for (int i = n; i > 1; i--) {
    Minus(1, 1, n, a[i]), Delete(1, 1, n, a[i]);
    while (v[1].mn1 <= 0) {
      Mark(1, 1, n);
    }
    w -= f[i], ans[i - 1] = w;
  }
  for (int i = u ? 1 : n; i <= n; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
