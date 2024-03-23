#include <fstream>
#define LL long long

using namespace std;

ifstream cin("prefix.in");
ofstream cout("prefix.out");

const LL kMod = 998244353;
LL n, p, ans;

LL Pow(LL x, LL y) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
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
  cin >> n >> p;
  for (LL i = 0, j = 1, k = 1; i <= n; i = j + 1, j = min(j * p, n), k = k * p % kMod) {
    ans = (ans + (i ? (Pow(p, j - i + 1) - 1 + kMod) % kMod : p) * Pow(p, i - 1) % kMod * k % kMod) % kMod;
  }
  cout << ans * Pow(p, kMod - n - 1) % kMod;
  return 0;
}
