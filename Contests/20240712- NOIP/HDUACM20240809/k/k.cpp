#include <fstream>
#define LL long long

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

int t;
LL x, y;

LL Gcd(LL x, LL y) {
  return y ? Gcd(y, x % y) : x;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> x >> y;
    LL z = Gcd(x, y);
    if (y > z && y / z % 2) {
      cout << y << ' ' << x / Gcd(x, y) * 2 << '\n';
    } else {
      cout << y << ' ' << x / Gcd(x, y) << '\n';
    }
  }
  return 0;
}
