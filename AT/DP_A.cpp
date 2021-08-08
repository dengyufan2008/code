#include <iostream>
#define LL long long

using namespace std;

LL n, h[100002], f[100002];

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> h[i];
  }
  fill(&f[2], &f[100000] + 1, 1145141919810);
  for (LL i = 1; i < n; i++) {
    f[i + 1] = min(f[i + 1], f[i] + abs(h[i] - h[i + 1]));
    f[i + 2] = min(f[i + 2], f[i] + abs(h[i] - h[i + 2]));
  }
  cout << f[n] << endl;
  return 0;
}
