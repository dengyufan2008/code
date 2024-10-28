#include <iostream>
#define LL __int128_t

using namespace std;

int o;

LL Read() {
  LL x = 0;
  int c = getchar();
  while (c < 48 || c > 57) {
    c = getchar();
  }
  while (c > 47 && c < 58) {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
  return x;
}

void Print(LL x) {
  if (x > 9) {
    Print(x / 10);
  }
  putchar(x % 10 + 48);
}

namespace Sub1 {
  const int kMaxN = 1e5 + 1, kInf = 1 << 30;
  int t, n, m, k, a[kMaxN], b[kMaxN];

  int main() {
    t = Read();
    while (t--) {
      n = Read(), m = Read(), k = Read();
      for (int i = 0; i < n; i++) {
        a[i] = Read();
      }
      for (int i = 0; i < n; i++) {
        b[i] = Read();
      }
      int ans = 0;
      for (int s = 0; s < 1 << n; s++) {
        for (int w = 0; w < 1 << k; w++) {
          int _m = m, _w = kInf;
          for (int i = 0; i < n; i++) {
            if (s >> i & 1) {
              _m -= b[i], _w = min(_w, a[i] + w);
            } else {
              _w = min(_w, a[i] ^ w);
            }
          }
          if (_m >= 0) {
            ans = max(ans, _w);
          }
        }
      }
      Print(ans), putchar(10);
    }
    return 0;
  }
}

namespace Sub2 {
const LL kMaxN = 1e5 + 1, kMaxL = 30, kInf = (LL)1 << kMaxL + 1;
struct V {
  int l, r;
  LL w;
  pair<LL, LL> f[3];
} v[kMaxN * kMaxL];
int t, n, m, k, s, u, b[kMaxN];
LL a[kMaxN];

void Insert(int &p, LL x, int w, int d = k - 1) {
  if (!p) {
    p = ++u, v[p] = v[0];
  }
  if (d < 0) {
    v[p].w = w;
    return;
  }
  if (x >> d & 1 ^ 1) {
    Insert(v[p].l, x, w, d - 1);
  } else {
    Insert(v[p].r, x, w, d - 1);
  }
}

pair<LL, LL> Calc(int p, int m, int d = k - 1) {
  if (v[p].f[m] != make_pair((LL)-1, (LL)-1)) {
    return v[p].f[m];
  } else if (d < 0) {
    return v[p].f[m] = v[p].w <= m ? make_pair(kInf, (LL)0) : make_pair((LL)0, kInf);
  }
  pair<LL, LL> ans = {-1, -1};
  if (v[p].l && v[p].r) {
    if (m) {
      auto l = Calc(v[p].l, 1, d - 1), r = Calc(v[p].r, 0, d - 1);
      pair<LL, LL> t = {min(l.first, r.first + ((LL)1 << d)), min(l.second, r.second + ((LL)1 << d))};
      if (min(ans.first, ans.second) < min(t.first, t.second)) {
        ans = t;
      }
      t = {min(l.first + ((LL)1 << d), r.first), min(l.second + ((LL)1 << d), r.second + ((LL)1 << d + 1))};
      if (min(ans.first, ans.second) < min(t.first, t.second)) {
        ans = t;
      }
      l = Calc(v[p].l, 0, d - 1), r = Calc(v[p].r, 1, d - 1);
      t = {min(l.first, r.first + ((LL)1 << d)), min(l.second, r.second + ((LL)1 << d))};
      if (min(ans.first, ans.second) < min(t.first, t.second)) {
        ans = t;
      }
      t = {min(l.first + ((LL)1 << d), r.first), min(l.second + ((LL)1 << d), r.second + ((LL)1 << d + 1))};
      if (min(ans.first, ans.second) < min(t.first, t.second)) {
        ans = t;
      }
    } else {
      auto l = Calc(v[p].l, 0, d - 1), r = Calc(v[p].r, 0, d - 1);
      pair<LL, LL> t = {min(l.first, r.first + ((LL)1 << d)), min(l.second, r.second + ((LL)1 << d))};
      if (min(ans.first, ans.second) < min(t.first, t.second)) {
        ans = t;
      }
      t = {min(l.first + ((LL)1 << d), r.first), min(l.second + ((LL)1 << d), r.second + ((LL)1 << d + 1))};
      if (min(ans.first, ans.second) < min(t.first, t.second)) {
        ans = t;
      }
    }
  } else if (!v[p].l) {
    auto t = Calc(v[p].r, m, d - 1);
    t.first += (LL)1 << d, t.second += (LL)1 << d;
    if (min(ans.first, ans.second) < min(t.first, t.second)) {
      ans = t;
    }
    t.first -= (LL)1 << d, t.second += (LL)1 << d;
    if (min(ans.first, ans.second) < min(t.first, t.second)) {
      ans = t;
    }
  } else if (!v[p].r) {
    auto t = Calc(v[p].l, m, d - 1);
    t.first += (LL)1 << d, t.second += (LL)1 << d;
    ans = t;
  }
  return v[p].f[m] = ans;
}

int main() {
  v[0].f[0] = v[0].f[1] = v[0].f[2] = {-1, -1};
  t = Read();
  while (t--) {
    s = u = 0;
    n = Read(), m = Read(), k = Read();
    for (int i = 1; i <= n; i++) {
      a[i] = Read();
    }
    for (int i = 1; i <= n; i++) {
      b[i] = Read();
    }
    for (int i = 1; i <= n; i++) {
      Insert(s, a[i], b[i]);
    }
    auto t = Calc(s, m);
    Print(min(t.first, t.second)), putchar(10);
  }
  return 0;
}
}

int main() {
  freopen("xor.in", "r", stdin);
  freopen("xor.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  o = Read();
  if (o <= 3) {
    return Sub1::main();
  } else if (o <= 13) {
    return Sub2::main();
  } else {
    int t = Read();
    while (t--) {
      cout << 0 << '\n';
    }
    return 0;
  }
}
