#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, ans, s, p, l, r, mid;

int Q(int l, int r) {
  int x;
  cout << "? " << l << " " << r << endl;
  cout.flush();
  cin >> x;
  return x;
}

int main() {
  cin >> n;
  s = Q(1, n);
  if (s == 1 || Q(1, s) != s) {
    l = s + 1, r = n;
    while (l <= r) {
      mid = (l + r) / 2, p = Q(s, mid);
      if (p == s) {
        r = mid - 1, ans = mid;
      } else {
        l = mid + 1;
      }
    }
  } else {
    l = 1, r = s - 1;
    while (l <= r) {
      mid = (l + r) / 2, p = Q(mid, s);
      if (p == s) {
        l = mid + 1, ans = mid;
      } else {
        r = mid - 1;
      }
    }
  }
  cout << "! " << ans << endl;
  cout.flush();
  return 0;
}
