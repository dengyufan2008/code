#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("assign.in");
ofstream cout("assign.out");

const int kMaxN = 1e5 + 1, kMod = 1e9 + 7;
int t, n, m, v;
LL ans;
pair<int, int> a[kMaxN];

LL Pow(LL x, LL y) {
  LL ans = 1;
  y %= kMod - 1;
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
    cin >> n >> m >> v;
    for (int i = 1; i <= m; i++) {
      cin >> a[i].first >> a[i].second;
    }
    sort(a + 1, a + m + 1), m = unique(a + 1, a + m + 1) - a - 1;
    ans = Pow(v, (a[1].first - 1 + n - a[m].first) * 2);
    for (int i = 2; i <= m; i++) {
      int l = a[i].first - a[i - 1].first;
      if (l == 0) {
        ans = 0;
      } else {
        LL w = Pow(v, l * 2) - Pow(v, l) + Pow(v, l - 1) + kMod;
        ans = ans * w % kMod;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
