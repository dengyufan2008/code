#include <bits/stdc++.h>
#define LL long long

using namespace std;

int l, mx;
LL m, _l, _r, mid, ans = -1;
char x[61];

bool C(LL k) {
  LL tot = 0, num = 1;
  for (int i = l - 1; i >= 0; i--) {
    if (i != l - 1) {
      if (__int128(num) * k > __int128(m)) {
        return false;
      }
      num *= k;
    }
    if (__int128(num) * x[i] > __int128(m) || tot + num * x[i] > m) {
      return false;
    }
    tot += num * x[i];
  }
  return tot <= m;
}

int main() {
  cin >> x >> m;
  for (; x[l]; l++) {
    mx = max(mx, (int)(x[l] -= '0'));
  }
  if (l == 1) {
    cout << (x[0] <= m) << endl;
    return 0;
  }
  _l = mx + 1, _r = 1e18 + 1;
  while (_l <= _r) {
    mid = (_l + _r) >> 1;
    if (C(mid)) {
      _l = mid + 1, ans = mid;
    } else {
      _r = mid - 1;
    }
  }
  cout << (ans != -1 ? ans - mx : 0) << endl;
  return 0;
}
