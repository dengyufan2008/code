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
    tot = flag = 0;
    cin >> n;
    for (LL i = 1; i <= n; i++) {
      cin >> h;
      tot += h;
      if (((i - 1) * i / 2) > tot) {
        flag = true;
      }
    }
    cout << (flag ? "NO" : "YES") << endl;
  }
  return 0;
}
