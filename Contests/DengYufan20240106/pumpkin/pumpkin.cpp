#include <fstream>
#define LL long long

using namespace std;

ifstream cin("pumpkin.in");
ofstream cout("pumpkin.out");

const LL kMod = 998244353;
LL n, m, xa, xb, xc, ya, yb, yc;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  n--, xa = 1, xb = 0, xc = 1, ya = kMod - 2, yb = 1, yc = 0;
  for (LL i = 1;; i++) {
    LL w = i % 3 == 2 ? i / 3 * 2 + 2 : 1;
    if (n >= w) {
      n -= w, m = (m + xc * w % kMod) % kMod;
      xa = (xa - ya * w % kMod + kMod) % kMod;
      xb = (xb - yb * w % kMod + kMod) % kMod;
      yc = (yc + xc * w % kMod) % kMod;
      swap(xa, ya), swap(xb, yb), swap(xc, yc);
    } else {
      m = (m + xc * n % kMod) % kMod;
      xa = (xa - ya * n % kMod + kMod) % kMod;
      xb = (xb - yb * n % kMod + kMod) % kMod;
      cout << (m + xc) % kMod << ' ' << xa << ' ' << xb << '\n';
      break;
    }
  }
  return 0;
}
