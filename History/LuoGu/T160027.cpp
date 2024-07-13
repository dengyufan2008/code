#include <iostream>
#define LL long long

using namespace std;

LL n, t, a[100001] = {1}, l, r;

int main() {
  cin >> n >> t;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i] = a[i] * a[i - 1];
  }
  for (int i = 1; i <= t; i++) {
    cin >> l >> r;
    cout << (a[r] / a[l - 1]) % 1000000007 << endl;
  }
  return 0;
}
