#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 1e6 + 1;
int n, a[kMaxN], b[kMaxN];
LL ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  for (int i = 1, j = 1; i <= n; !a[i] && i++) {
    for (; j <= n && a[i]; !b[j] && j++) {
      int t = min(a[i], b[j]);
      a[i] -= t, b[j] -= t, ans += t * abs(i - j);
    }
  }
  cout << ans;
  return 0;
}
