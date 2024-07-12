#include <fstream>
#define LL long long

using namespace std;

ifstream cin("plant.in");
ofstream cout("plant.out");

const LL kMaxN = 1e6 + 1, kMod = 998244353, kInv2 = kMod + 1 >> 1;
LL n, m, ans, a[kMaxN], b[kMaxN], pw[kMaxN];

LL Pow(LL x, LL y = kMod - 2) {
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
  pw[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i] = pw[i - 1] * kInv2 % kMod;
  }
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    a[x]++, a[y + 1]--;
    cin >> x >> y;
    b[x]++, b[y + 1]--;
  }
  for (int i = 1; i <= n; i++) {
    a[i] += a[i - 1], b[i] += b[i - 1];
    ans = (ans + (1 - pw[a[i] + b[i]] + kMod) % kMod * a[i] % kMod * Pow(a[i] + b[i]) % kMod) % kMod;
  }
  cout << ans;
  return 0;
}
