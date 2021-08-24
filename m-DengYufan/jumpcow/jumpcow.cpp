#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

LL p, a[150001], f[150001][2];

int main() {
  freopen("jumpcow.in", "r", stdin);
  freopen("jumpcow.out", "w", stdout);
  cin >> p;
  for (LL i = 1; i <= p; i++) {
    cin >> a[i];
  }
  for (LL i = 1; i <= p; i++) {
    f[i][0] = max(f[i - 1][1] - a[i], f[i - 1][0]);
    f[i][1] = max(f[i - 1][0] + a[i], f[i - 1][1]);
  }
  cout << max(f[p][0], f[p][1]) << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
