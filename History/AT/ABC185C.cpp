#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL l, ans = 1;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> l;
  for (int i = 1; i <= 11; i++) {
    ans *= (l - i);
    ans /= i;
  }
  cout << ans << endl;
  return 0;
}
