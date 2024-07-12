#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

LL n, a, b, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> a >> b;
  if (b >= n) {
    ans = n;
  } else if (a == 1 && b <= 1000000) {
    for (LL i = 1; i <= b; i++) {
      ans += (n - i) / (2 * b) + 1;
    }
  } else {
    ans = n - (n - b) / a;
    for (LL i = a, j = b;;) {
      LL l = 1, r = (n - j) / i;
      while (l <= r) {
        LL mid = l + r >> 1;
        if (a * (i * mid + j) + b <= n) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      ans += r - max(r - b, 0LL) / a;
      if (a * i <= n && a * a * i <= n && a * j <= n &&
          a * a * j <= n && a * a * j + a * b + b <= n) {
        i = a * a * i, j = a * a * j + a * b + b;
      } else {
        break;
      }
    }
  }
  cout << ans;
  return 0;
}
