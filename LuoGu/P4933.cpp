#include <iostream>
#define LL long long

using namespace std;

const int kMod = 998244353;
int n, ans, h[1001], f[1001][40001];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> h[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      int d = h[i] - h[j];
      f[i][d + 20000] = (f[i][d + 20000] + f[j][d + 20000] + 1) % kMod;
    }
  }
  for (int i = 0; i <= 40000; i++) {
    ans = (ans + f[n][i]) % kMod;
  }
  cout << (ans + n) % kMod << endl;
  return 0;
}
