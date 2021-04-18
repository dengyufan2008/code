#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, k, l, r, mid, ans, a[200002], b[200002];

bool C(int x) {
  b[0] = 0;
  for (int i = 1; i <= n; i++) {
    b[i] = b[i - 1] + (a[i] >= x ? 1 : -1);
  }
  for (int i = k, tmp = 0; i <= n; i++) {
    tmp = min(tmp, b[i - k]);
    if (b[i] > tmp) {
      return true;
    }
  }
  return false;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  l = 1, r = n;
  while (l <= r) {
    mid = (l + r) / 2;
    if (C(mid)) {
      ans = max(ans, mid);
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << ans;
  return 0;
}
