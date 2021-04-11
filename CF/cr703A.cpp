#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, h, tot;
bool flag;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    tot = flag = 0;
    for (int i = 1; i <= n; i++) {
      cin >> h;
      tot += h;
      flag = (tot >= i * (i - 1) / 2);
    }
    cout << (flag ? "YES" : "NO") << endl;
  }
  return 0;
}
