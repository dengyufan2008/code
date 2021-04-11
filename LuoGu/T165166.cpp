#include <iostream>
#define LL long long

using namespace std;

LL n, k, a[100001], l, r, mid, k2, ans = 100000;

LL FindK(LL m) {
  LL k1 = 0, num = 0;
  for (LL i = 1; i <= n; i++) {
    if (num + a[i] > m) {
      num = 0;
      k1++;
    }
    num = num + a[i];
  }
  k1++;
  return k1;
}

int main() {
  cin >> n >> k;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
    l = max(l, a[i]);
    r = r + a[i];
  }

  do {
    mid = (l + r) / 2, k2 = FindK(mid);
    if (k2 == k) {
      if (mid < ans) {
        ans = mid;
      }
      r = mid - 1;
    } else if (k2 > k) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  } while (l <= r);

  cout << ans;
  return 0;
}
