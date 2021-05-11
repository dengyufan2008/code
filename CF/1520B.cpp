#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxM[10] = {1, 11, 111, 1111, 11111, 111111, 1111111, 11111111, 111111111, 1111111111};

int t, n, l, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    l = 0;
    cin >> n;
    for (int i = 10; i <= n; i *= 10) {
      l++;
    }
    ans = l * 9;
    for (int i = kMaxM[l]; i <= n; i += kMaxM[l]) {
      ans++;
    }
    cout << ans << endl;
  }
  return 0;
}
