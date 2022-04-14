#include <iostream>
#define LL long long

using namespace std;

int n;
double m, ans, a[100001];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    m += a[i];
  }
  m /= n;
  for (int i = 1; i <= n; i++) {
    ans += (a[i] - m) * (a[i] - m);
  }
  cout << m << ' ' << ans / n << '\n';
  return 0;
}
