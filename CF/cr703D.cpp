#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, k, l, r, mid, ans, a[200001];

bool C(int x) {
  int b[200001] = {-2};  //后缀最大值
  for (int i = 1, tmp = 0; i <= n; i++) {
    tmp += (a[i] >= x ? 1 : -1);
    b[i] = max(b[i - 1], tmp);
  }
  for (int i = n; i >= k; i--) {
    if (b[i - k + 1] > 0) {
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
