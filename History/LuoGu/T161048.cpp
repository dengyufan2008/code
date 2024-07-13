#include <iostream>
#define LL long long

using namespace std;

const LL kMax = 1000000;
LL n, m, a[2 * kMax + 1];

int main() {
  cin >> n >> m;
  a[kMax] = 1;
  for (LL i = kMax + 1; i <= kMax + n; i++) {
    for (LL j = i - m; j < i; j++) {
      a[i] = (a[i] + a[j]) % 1000000007;
    }
  }
  cout << a[kMax + n] % 1000000007;
  return 0;
}
