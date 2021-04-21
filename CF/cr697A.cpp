#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, i;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (i = 1; i <= n; i <<= 1) {
    }
    cout << (i == n ? "NO" : "YES") << endl;
  }
  return 0;
}
