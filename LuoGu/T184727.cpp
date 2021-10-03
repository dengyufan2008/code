#include <cmath>
#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int t, n, p, ans;

int main() {
  cin >> t;
  while (t--) {
    ans = 0;
    cin >> n >> p;
    for (int i = 1; i <= n; i++) {
      if (i % p) {
        ans += (log2(n / i) / log2(p) + 1) / 2;
      }
    }
    cout << ans << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
/*
1...
3...

1...
2...
3...
4...
6...
7...
8...
9...
*/