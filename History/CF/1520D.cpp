#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 200000;

LL t, n, ans, a[2 * kMaxN + 1];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    ans = 0;
    fill(&a[1], &a[2 * kMaxN], 0);
    cin >> n;
    for (LL i = 1, tmp; i <= n; i++) {
      cin >> tmp;
      ans += a[tmp - i + kMaxN]++;
    }
    cout << ans << endl;
  }
  return 0;
}
