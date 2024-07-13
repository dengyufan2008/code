#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, w, h, n, a1, a2;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> w >> h >> n;
    for (a1 = 1; !(w % (a1 << 1)); a1 <<= 1) {
    }
    for (a2 = 1; !(h % (a2 << 1)); a2 <<= 1) {
    }
    cout << (a1 * a2 >= n ? "YES" : "NO") << endl;
  }
  return 0;
}
