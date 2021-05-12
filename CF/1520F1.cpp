#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, t, k, l, r, mid, v;

int Q(int x, int y) {
  int ans;
  cout << "? " << x << " " << y << endl;
  cout.flush();
  cin >> ans;
  return y - x + 1 - ans;
}

void A(int x) {
  cout << "! " << x << endl;
  cout.flush();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> t;
  while (t--) {
    cin >> k;
    l = 1, r = n;
    while (l <= r) {
      mid = (l + r) >> 1;
      v = Q(l, mid);
      if (v < k) {
        l = mid + 1, k -= v;
      } else {
        r = mid - 1;
      }
    }
    A(l);
  }
  return 0;
}
