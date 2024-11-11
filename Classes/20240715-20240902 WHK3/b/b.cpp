#include <chrono>
#include <fstream>
#include <random>
#include <unordered_map>
#define LL long long
#define ULL unsigned LL

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 2e5 + 2;
int n, m, b[kMaxN];
LL ans;
ULL w[kMaxN];
unordered_map<ULL, pair<int, LL>> s;
mt19937_64 Rand(chrono::steady_clock().now().time_since_epoch().count());

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, l, r; i <= n; i++) {
    cin >> l >> r;
    ULL o = Rand();
    w[l] ^= o, w[r] ^= o;
    b[l]++, b[r + 1]--;
  }
  for (int i = 1; i <= m; i++) {
    w[i] ^= w[i - 1];
  }
  for (int i = 1; i <= m; i++) {
    w[i] ^= w[i - 1];
  }
  for (int i = 0; i < m; i++) {
    auto &o = s[w[i]];
    o.first++, o.second += i;
    ans += 1LL * (i + 1) * o.first - o.second;
  }
  for (int i = 1; i <= m; i++) {
    b[i] += b[i - 1];
  }
  for (int i = 1, j = 1; i <= m; i = j) {
    for (; j <= m && (b[j] > 0) == (b[i] > 0); j++) {
    }
    if (!b[i]) {
      int o = j - i;
      ans -= 1LL * o * (o + 1) * (o + 2) / 6;
    }
  }
  cout << ans << '\n';
  return 0;
}
