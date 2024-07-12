#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 3e5 + 1;
struct V {
  int l, r, d;
} v[kMaxN * 48];
int n, m, _m, _v, w1, w2, a[kMaxN], b[kMaxN], c[kMaxN], t[kMaxN], s[kMaxN];

int Read() {
  int x = 0, c = getchar();
  while (c < 48 || c > 57) {
    c = getchar();
  }
  while (c > 47 && c < 58) {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
  return x;
}

void Add(int &p, int l, int r, int x) {
  v[++_v] = v[p], p = _v;
  if (l == r) {
    v[p].d++;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Add(v[p].l, l, mid, x);
  } else {
    Add(v[p].r, mid + 1, r, x);
  }
  v[p].d = v[v[p].l].d + v[v[p].r].d;
}

int Ask(int p, int l, int r, int x) {
  if (!p) {
    return 0;
  } else if (l >= x) {
    return v[p].d;
  }
  int mid = l + r >> 1, ans = Ask(v[p].r, mid + 1, r, x);
  if (mid >= x) {
    ans += Ask(v[p].l, l, mid, x);
  }
  return ans;
}

void Init() {
  sort(t + 1, t + n + 1, [](int i, int j) { return a[i] < a[j]; });
  for (int i = 1; i <= n; i++) {
    b[t[i]] = b[t[i - 1]] + (a[t[i]] != a[t[i - 1]]);
    c[b[t[i]]] = a[t[i]];
  }
  _v = 0;
  for (int i = 1; i <= n; i++) {
    Add(s[i] = s[i - 1], 1, b[t[n]], b[i]);
  }
}

int Calc(int x, int y, int z) {
  int l = 1, r = b[t[n]];
  while (l <= r) {
    int mid = l + r >> 1;
    if (Ask(s[y], 1, b[t[n]], mid) - Ask(s[x - 1], 1, b[t[n]], mid) >= z) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return c[r];
}

int main() {
  freopen("wow.in", "r", stdin);
  freopen("wow.out", "w", stdout);
  n = Read(), m = Read();
  for (int i = 1; i <= n; i++) {
    a[i] = Read(), t[i] = i;
  }
  _m = 1, Init();
  for (int o, x, y, z, u = b[t[n]]; _m <= m && u > 2; _m++) {
    o = Read(), x = Read();
    if (o == 1) {
      u = 0;
      for (int i = 1; i <= b[t[n]]; i++) {
        c[i] = c[i] + x >> 1;
        u += c[i] != c[i - 1];
      }
    } else {
      y = Read(), z = Read();
      printf("%d\n", Calc(x, y, z));
    }
  }
  for (int i = 1; i <= b[t[n]]; i++) {
    if (!w1) {
      w1 = c[i];
    } else if (w1 != c[i]) {
      w2 = c[i];
    }
  }
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + (c[b[i]] == w2);
  }
  for (int o, x, y, z; _m <= m; _m++) {
    o = Read(), x = Read();
    if (o == 1) {
      w1 = w1 + x >> 1, w2 = w2 + x >> 1;
    } else {
      y = Read(), z = Read();
      printf("%d\n", s[y] - s[x - 1] >= z ? w2 : w1);
    }
  }
  return 0;
}
