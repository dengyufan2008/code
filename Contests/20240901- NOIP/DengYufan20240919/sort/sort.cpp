#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("sort.in");
ofstream cout("sort.out");

const int kMaxN = 1e6 + 1, kMod = 1e9 + 7;
int n, a[kMaxN];
LL ans, fact[kMaxN];
bool u;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  cin >> n >> u;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i < n; i++) {
    ans += 2LL * (a[i + 1] - a[i]) * min(i, n - i);
  }
  cout << ans << " \n"[!u];
  if (u) {
    ans = fact[n / 2] * fact[n / 2] % kMod * 2 % kMod;
    if (n & 1) {
      ans = ans * n % kMod;
    }
    cout << ans << '\n';
  }
  return 0;
}
