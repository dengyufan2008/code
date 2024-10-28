#include <iostream>
#define LL __int128_t

using namespace std;

const int kMaxN = 1e5 + 1, kMaxM = 120;
struct V {
  int s[2];
  LL w;
} v[kMaxN * kMaxM];
int t, n, m, k, s, u, b[kMaxN];
LL mn, a[kMaxN];

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

void Insert(int &p, LL x, int w, int d) {
  !p && (v[++u] = v[0], p = u);
  if (d < 0) {
    v[p].w += w;
    return;
  }
  Insert(v[p].s[x >> d & 1], x, w, d - 1);
  v[p].w = v[v[p].s[0]].w + v[v[p].s[1]].w;
}

LL M(int p, int m, LL mn, int d) {
  if (m >= v[p].w) {
    return mn + ((LL)1 << d + 1) - 1;
  } else if (d < 0) {
    return min(mn, (LL)0);
  }
  LL ans = 0, w = (LL)1 << d;
  if (m >= v[v[p].s[0]].w && mn > 0 || m >= v[v[p].s[1]].w && mn > -w) {
    if (m >= v[v[p].s[0]].w && mn > 0) {
      ans = max(ans, M(v[p].s[1], m - v[v[p].s[0]].w, mn - w, d - 1) + w);
    }
    if (m >= v[v[p].s[1]].w && mn > -w) {
      ans = max(ans, M(v[p].s[0], m - v[v[p].s[1]].w, mn, d - 1) + w);
    }
  } else {
    ans = max(ans, M(v[p].s[0], m, mn, d - 1));
    ans = max(ans, M(v[p].s[1], m, mn + w, d - 1));
  }
  return ans;
}

int main() {
  freopen("xor.in", "r", stdin);
  freopen("xor.out", "w", stdout);
  ios::sync_with_stdio(0);
  Read(), t = Read();
  while (t--) {
    s = u = 0, mn = (LL)1 << kMaxM;
    n = Read(), m = Read(), k = Read();
    for (int i = 1; i <= n; i++) {
      a[i] = Read();
    }
    for (int i = 1; i <= n; i++) {
      b[i] = Read();
    }
    for (int i = 1; i <= n; i++) {
      mn = min(mn, a[i]);
      Insert(s, a[i], b[i], k - 1);
    }
    Print(M(s, m, mn, k - 1)), putchar(10);
  }
  return 0;
}
