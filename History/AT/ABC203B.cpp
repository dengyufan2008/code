#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, k, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      ans += i * 100 + j;
    }
  }
  cout << ans << endl;
  return 0;
}
