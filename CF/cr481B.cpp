#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, num, ans;
char ch;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> ch;
    if (ch == 'x') {
      num++;
    } else {
      ans += max(num - 2, 0);
      num = 0;
    }
  }
  ans += max(num - 2, 0);
  cout << ans;
  return 0;
}
