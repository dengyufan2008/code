#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const LL kMod = 19650827;
LL n, h[1001], d[1001][1001][2];

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> h[i];
    d[i][i][0] = 1;
  }
  for (LL i = 2; i <= n; i++) {
    for (LL j = 1, k; (k = j + i - 1) <= n; j++) {
      d[j][k][0] = (d[j + 1][k][0] * (h[j + 1] > h[j]) + d[j + 1][k][1] * (h[k] > h[j])) % kMod;
      d[j][k][1] = (d[j][k - 1][0] * (h[j] < h[k]) + d[j][k - 1][1] * (h[k - 1] < h[k])) % kMod;
    }
  }
  cout << (d[1][n][0] + d[1][n][1]) % kMod << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
