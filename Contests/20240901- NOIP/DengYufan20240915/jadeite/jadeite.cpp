#include <fstream>
#define LL long long

using namespace std;

ifstream cin("jadeite.in");
ofstream cout("jadeite.out");

const int kMod = 998244353, kInv6 = 166374059;
int t;
LL n, m, _m, ans;

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m, _m = Pow(m), ans = 0;
    for (int i = 1; i < m; i++) {
      LL j = i * _m % kMod, _j = Pow(j - 1);
      ans = (ans + ((Pow(j, n + 2) - 1) * _j - j - 1 - j * n) % kMod * _j % kMod * i) % kMod;
    }
    ans = (ans + m * n * (n + 1) / 2) % kMod;
    ans = (ans + kMod) * Pow((n * (n + 1) / 2) % kMod) % kMod;
    cout << ans << '\n';
  }
  return 0;
}
