#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL ans;
long double a, b, c;

int main() {
  cin >> a >> b >> c;
  c += 1e-14;
  for (LL i = ceil(a - c); i <= floor(a + c); i++) {
    ans += floor(b + sqrt(c * c - (a - i) * (a - i))) - ceil(b - sqrt(c * c - (a - i) * (a - i))) + 1;
  }
  cout << ans << endl;
  return 0;
}
