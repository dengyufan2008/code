#include <iostream>
#define LL long long

using namespace std;

const LL kMod = 1e9 + 7;
LL n, k, a[2001], d[2001];

LL Pow(LL x, LL y) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

LL Feb(LL x, LL y) {
  LL ans = 1;
  for (LL i = 1; i < y; i++) {
    ans = ans * (x + y - i - 1) % kMod * Pow(i, kMod - 2) % kMod;
  }
  return ans;
}

int main() {
  cin >> n >> k;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
    d[i] = Feb(k, i);
  }
  for (LL i = 1; i <= n; i++) {
    LL ans = 0;
    for (LL j = i; j; j--) {
      ans = (ans + d[j] * a[i - j + 1] % kMod) % kMod;
    }
    cout << ans << ' ';
  }
  return 0;
}
