#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("merchant.in");
ofstream cout("merchant.out");

const LL kMaxN = 2e6 + 1, kMaxV = 2e18;
struct A {
  LL k, b;
  LL Calc(LL x) { return k * x + b; }
} a[kMaxN];
int n, m, l[kMaxN];
LL w;

bool CheckW(LL x) {
  if (x) {
    for (int i = 1; i <= n; i++) {
      if (w >= a[i].b) {
        if (a[i].k >= (w - a[i].b + x - 1) / x) {
          return 1;
        }
      } else {
        if (a[i].k >= (w - a[i].b) / x) {
          return 1;
        }
      }
    }
  }
  nth_element(l + 1, l + m, l + n + 1, [x](int i, int j) {
    return a[i].Calc(x) > a[j].Calc(x);
  });
  LL s = 0;
  for (int i = 1; i <= m; i++) {
    LL t = a[l[i]].Calc(x);
    if (t > 0) {
      s += t;
      if (s >= w) {
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> w;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].k >> a[i].b;
  }
  for (int i = 1; i <= n; i++) {
    l[i] = i;
  }
  if (CheckW(0)) {
    cout << 0 << '\n';
    return 0;
  }
  LL l = 1, r = kMaxV;
  while (l <= r) {
    LL mid = l + r >> 1;
    if (CheckW(mid)) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << l << '\n';
  return 0;
}
