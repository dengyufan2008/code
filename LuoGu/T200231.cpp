#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, q, k, ans, x[3000001];

int Find(int k) {
  int l = 1, r = n, mid, ans = 0;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (x[mid] > k) {
      mid = r - 1;
    } else {
      mid = l + 1;
      ans = max(ans, mid);
    }
  }
  k = 2 * x[ans] - k, l = 1, r = n, ans = 0;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (x[mid] > k) {
      mid = r - 1;
    } else {
      mid = l + 1;
      ans = max(ans, mid);
    }
  }
  return k == x[ans] ? 0 : k;
}

int main() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> x[i];
  }
  sort(x + 1, x + n + 1);
  while (q--) {
    cin >> k;
    while (k = Find(k)) {
      ans++;
    }
    cout << ans << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
