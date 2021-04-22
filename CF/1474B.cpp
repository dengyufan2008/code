#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, d, ans;

bool C(int x) {
  for (int i = d + 1; i <= sqrt(x); i++) {
    if (!(x % i) && x / i - i >= d) {
      return true;
    }
  }
  return false;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> d;
    for (ans = 6; !C(ans); ans++) {
    }
    cout << ans << endl;
  }
  return 0;
}
