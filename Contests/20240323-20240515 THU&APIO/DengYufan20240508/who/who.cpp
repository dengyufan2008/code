#include <fstream>
#define LL long long

using namespace std;

ifstream cin("who.in");
ofstream cout("who.out");

int t;
LL a, b, p, ans;

LL Mul(LL x, LL y) {
  return (__int128_t)x * (__int128_t)y % p;
}

LL Pow(LL x, LL y) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = Mul(ans, x);
    }
    x = Mul(x, x);
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    ans = 0;
    cin >> a >> b >> p;
    for (LL i = 0; i < p; i++) {
      LL x = (Mul(Mul(i, i), i) + Mul(a, i) + b) % p;
      if (!x || p == 2) {
        ans++;
      } else if (Pow(x, p - 1 >> 1) == 1) {
        ans += 2;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
