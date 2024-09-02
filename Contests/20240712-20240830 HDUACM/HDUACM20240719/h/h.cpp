#include <fstream>
#define LL long long

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

int t, n, k;
LL ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> k, ans = 1;
    for (int i = 0; i < k; i++) {
      if (n >> i & 1) {
        ans *= 12;
      } else {
        ans *= 4;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
