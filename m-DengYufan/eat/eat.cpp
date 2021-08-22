#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, ans, a[5000001], f[5000001];
char ch;

int main() {
  freopen("eat.in", "r", stdin);
  // freopen("eat.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> ch;
    a[i] = (ch == '1' ? 1 : -1) + a[i - 1];
  }
  for (int i = 1; i <= n; i++) {
    f[i] = ans;
    for (int j = 0; j < i; j++) {
      if (a[i] > a[j]) {
        f[i] = max(f[i], f[j] + i - j);
      }
    }
    ans = max(ans, f[i]);
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
