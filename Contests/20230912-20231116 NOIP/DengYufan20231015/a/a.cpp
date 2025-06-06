#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

const LL kMaxN = 2e6 + 1;
LL n, t, ans, a[kMaxN], pre[kMaxN], suf[kMaxN];
pair<LL, LL> q[kMaxN];

LL Read() {
  LL x = 0;
  char c = getchar();
  while (c < '0' || c > '9') {
    c = getchar();
  }
  while (c > '/' && c < ':') {
    x = (x << 3) + (x << 1) + (c - '0');
    c = getchar();
  }
  return x;
}

int main() {
  // freopen("a.in", "r", stdin);
  // freopen("a.out", "w", stdout);
  n = Read();
  for (LL i = 1; i <= n; i++) {
    a[i] = Read();
  }
  t = 0;
  for (LL i = 1; i <= n; i++) {
    for (; t && q[t].first >= a[i]; t--) {
    }
    if (t) {
      pre[i] = q[t].second;
    } else {
      pre[i] = 0;
    }
    q[++t] = {a[i], i};
  }
  t = 0;
  for (LL i = n; i >= 1; i--) {
    for (; t && q[t].first > a[i]; t--) {
    }
    if (t) {
      suf[i] = q[t].second;
    } else {
      suf[i] = n + 1;
    }
    q[++t] = {a[i], i};
  }
  for (LL i = 1; i <= n; i++) {
    LL l = i - pre[i] - 1, r = suf[i] - i - 1;
    if (l <= r) {
      ans += l * (l + 1) >> 1;
    } else {
      ans += l * (r + 1) - (r * (r + 1) >> 1);
    }
  }
  printf("%lld", ans);
  return 0;
}
