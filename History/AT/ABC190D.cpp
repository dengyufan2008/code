#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (LL i = 1; i * (i + 1) <= n * 2; i++) {
    ans += i & 1 && !(n % i) || !(i & 1) && n & 1 && i % 4 && !(n % (i / 2)) && (n * 2 / i) % 2 || !(n % 2) && !(i % 4) && !(n % (i / 2)) && (n * 2 / i) % 2;
  }
  cout << ans * 2 << endl;
  return 0;
}
