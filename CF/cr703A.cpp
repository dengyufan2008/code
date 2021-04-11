#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, h, tot;

int main() {
  cin.tie(0), cout.tie(0);
  std::ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    tot = 0;
    for (int i = 1; i <= n; i++) {
      cin >> h;
      tot += h;
    }
    cout << (tot >= n * (n - 1) / 2 ? "YES" : "NO") << endl;
  }
  return 0;
}
