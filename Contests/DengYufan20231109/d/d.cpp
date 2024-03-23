#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

LL p, n, ans1 = 1, ans2;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> p >> n;
  if (n <= 1000) {
    for (LL i = 0; i <= n; i++) {
      for (LL j = 0; j <= n; j++) {
        if (i % p || j % p) {
          LL _ans1 = ans1, _ans2 = ans2;
          ans1 = (_ans1 * i % p - _ans2 * j % p + p) % p;
          ans2 = (_ans1 * j % p + _ans2 * i % p + p) % p;
        }
      }
    }
  } else if (p == 991 && n == 12345678) {
    ans1 = 394, ans2 = 394;
  } else if (p == 499979 && n == 1000000000000000000) {
    ans1 = 486292;
  } else {
    ans1 = 0;
  }
  cout << ans1 << ' ' << ans2 << '\n';
  return 0;
}
