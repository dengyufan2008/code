#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("as.in");
ofstream cout("as.out");

const int kMaxN = 1e6 + 1;
int n, m, k, ans = 1e9, a[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i < n; i++) {
    ans = min(ans, a[i] ^ a[i + 1]);
    for (int j = 1, l = 0, r = 0; j <= a[i + 1]; j <<= 1) {
      if (!(a[i] & j) && (a[i + 1] & j) && l > r && j - l <= k) {
        ans = min(ans, (a[i] + j - l) ^ (a[i + 1] + j - l));
      }
      if ((a[i] & j) && !(a[i + 1] & j) && l < r && j - r <= k) {
        ans = min(ans, (a[i] + j - r) ^ (a[i + 1] + j - r));
      }
      l |= (a[i] & j), r |= (a[i + 1] & j);
    }
  }
  cout << ans;
  return 0;
}
