#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL x, y, a, b, ans;

int main() {
  cin >> x >> y >> a >> b;
  while ((double)a * x <= 2e18 && a * x <= x + b && a * x < y) {
    x *= a;
    ans++;
  }
  cout << ans + (y - 1 - x) / b << endl;
}
