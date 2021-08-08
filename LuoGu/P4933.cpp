#include <iostream>
#define LL long long

using namespace std;

const LL kMod = 998244353;
LL n, ans, h[1001], f[1001][40001];

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> h[i];
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j < i; j++) {
      LL d = h[i] - h[j];
      f[i][d + 20000] = (f[i][d + 20000] + f[j][d + 20000] + 1) % kMod;
    }
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 0; j <= 40000; j++) {
      ans = (ans + f[i][j]) % kMod;
    }
  }
  cout << (ans + n) % kMod << endl;
  return 0;
}
