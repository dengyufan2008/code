#include <bitset>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("beautiful.in");
ofstream cout("beautiful.out");

const int kMaxN = 1e9 + 1, kMaxM = 50847535, kMod = 998244353;
int n, m, prime[kMaxM];
LL ans;
bitset<kMaxN> b;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n, b[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!b[i]) {
      prime[++m] = i;
    }
    for (int j = 1; j <= m; j++) {
      LL w = (LL)i * prime[j];
      if (w <= n) {
        b[w] = 1;
        if (!(i % prime[j])) {
          break;
        }
      } else {
        break;
      }
    }
  }
  ans = 1;
  for (int i = 1, j = 1; i <= m; i++) {
    if (prime[i] * 2 <= n) {
      LL w = prime[i];
      for (; w * 2 <= n; w *= prime[i]) {
      }
      if (w <= n) {
        ans = ans * 2 % kMod;
      }
    } else {
      ans = ans * ++j % kMod;
    }
  }
  cout << ans << '\n';
  return 0;
}
