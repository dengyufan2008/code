#include <iostream>
#define LL long long

using namespace std;

LL n, ans, t[102], f[102], _f[102];

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> t[i];
  }
  for (LL i = 1; i <= n; i++) {
    fill(&f[0], &f[101] + 1, 0), fill(&_f[0], &_f[101] + 1, 0);
    for (LL j = 1; j <= i; j++) {
      for (LL k = 0; k < j; k++) {
        if (t[k] < t[j]) {
          f[j] = max(f[j], f[k] + 1);
        }
      }
    }
    for (LL j = n; j >= i; j--) {
      for (LL k = n + 1; k > j; k--) {
        if (t[k] < t[j]) {
          _f[j] = max(_f[j], _f[k] + 1);
        }
      }
    }
    ans = max(ans, f[i] + _f[i] - 1);
  }
  cout << n - ans << endl;
  return 0;
}
