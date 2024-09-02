#include <fstream>
#define LL long long

using namespace std;

ifstream cin("sequence.in");
ofstream cout("sequence.out");

const int kMaxN = 1e6 + 1;
int t, n, a[kMaxN];
LL ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1, x = 0, y = 0, z = 0, w = 0; i <= n; i++, swap(y, z)) {
      a[i] = max(a[i] - x - z, 0);
      ans += max(a[i] - w, 0), w = 0;
      if (i < n && a[i + 1] < x + y) {
        z += a[i];
        int k = x + y - a[i + 1];
        if (x >= k && y >= k) {
          w = k, x -= k, y -= k;
        } else if (x >= k) {
          w = y, x -= k, y = 0;
        } else if (y >= k) {
          w = x, x = 0, y -= k;
        } else {
          w = a[i + 1], x = y = 0;
        }
      } else {
        int k = min(a[i], a[i + 1] - x - y);
        x += k, a[i] -= k, z += a[i];
      }
    }
    cout << ans << '\n', ans = 0;
  }
  return 0;
}
