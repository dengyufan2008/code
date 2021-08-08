#include <iostream>
#define LL long long

using namespace std;

LL n, k, h[100001], f[100001];

int main() {
  cin >> n >> k;
  for (LL i = 1; i <= n; i++) {
    cin >> h[i];
  }
  fill(&f[2], &f[100000] + 1, 1145141919810);
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= k; j++) {
      if (i + j <= n) {
        f[i + j] = min(f[i + j], f[i] + abs(h[i] - h[i + j]));
      }
    }
  }
  cout << f[n] << endl;
  return 0;
}
