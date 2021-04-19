#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, a;
bool flag;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    flag = false;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a;
      if (sqrt(a) != (int)sqrt(a)) {
        flag = true;
      }
    }
    cout << (flag ? "YES" : "NO") << endl;
  }
  return 0;
}
