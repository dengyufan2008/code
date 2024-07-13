#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, a, b, n, s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> a >> b >> n >> s;
    s -= min(a, s / n) * n;
    cout << (s <= b ? "YES" : "NO") << endl;
  }
  return 0;
}
