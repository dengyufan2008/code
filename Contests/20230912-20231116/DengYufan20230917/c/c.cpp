#include <iostream>
#define LL long long

using namespace std;

const LL kMaxN = 1e7 + 1;
LL t, n, m, ans, a[kMaxN], c[kMaxN];

template <LL T>
struct fast_io {
  char p[T], *p1, *p2;
  fast_io() {
    p1 = p2 = p;
    fread(p, 1, T, stdin);
  }
  char gc() {
    return *p1++;
  }
};
fast_io<110'000'000> io;
LL Read() {
  LL r = 0, neg = 1;
  char ch;
  do ch = io.gc();
  while (ch < 48 || ch > 57);
  do r = r * 10 + ch - 48, ch = io.gc();
  while (ch >= 48 && ch <= 57);
  return r;
}

int main() {
  // cin.tie(0), cout.tie(0);
  // ios::sync_with_stdio(0);
  t = Read();
  // cin >> t;
  while (t--) {
    n = Read(), m = Read();
    // cin >> n >> m;
    for (LL i = 1; i <= n; i++) {
      a[i] = Read();
      // cin >> a[i];
      c[a[i]]++;
    }
    for (LL i = 1, j = 1; i <= n; i++) {
      for (; !c[j]; j++) {
      }
      a[i] = j, c[j]--;
    }
    ans = 0;
    for (LL i = 1, j = 1; i <= n; i++, j++) {
      ans += a[i] - min(a[i], i), a[i] = i - min(a[i], i);
      while (j && !c[j]) {
        j--;
      }
      c[a[i]]++;
      if (j > a[i]) {
        ans += j - a[i], c[a[i]]++, c[j]--;
      }
    }
    for (LL i = 0; i <= n; i++) {
      c[i] = 0;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
