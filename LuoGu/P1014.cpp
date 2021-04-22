#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, l, r, mid, tmp;

int main() {
  cin >> n;
  l = 1, r = n;
  while (l < r) {
    mid = (l + r) >> 1;
    if (mid * (mid + 1) / 2 < n) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  tmp = n - l * (l - 1) / 2;
  if (l % 2 == 0) {
    cout << tmp << '/' << l + 1 - tmp;
  } else {
    cout << l + 1 - tmp << '/' << tmp;
  }
  return 0;
}
