#include <cmath>
#include <iostream>
#define LL long long

using namespace std;

const LL kMax = 1000000007;
LL n, t, b, a[100001], l, r;

int main() {
  cin >> n >> t >> b;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i < n; i++) {
    a[n - i] = a[n - i] * (LL)pow(b, i);
  }
  for (int i = n - 1; i >= 1; i--) {
    a[i] = a[i] + a[i + 1];
  }
  for (int i = 1; i <= t; i++) {
    cin >> l >> r;
    cout << ((a[l] - a[r + 1]) / (LL)pow(b, r + 1)) % kMax << endl;
  }
  return 0;
}
