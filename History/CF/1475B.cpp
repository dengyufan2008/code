#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    cout << (n % 2020 * 2020 < n ? "YES" : "NO") << endl;
  }
  return 0;
}
