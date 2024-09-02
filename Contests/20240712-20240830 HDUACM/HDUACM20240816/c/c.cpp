#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMod = 998244353;
int t, n;
LL s, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1, x; i <= n; i++) {
      cin >> x;
      ans = (ans + s * x % kMod * (s + x)) % kMod;
      s = (s + x) % kMod;
    }
    cout << ans << '\n', s = ans = 0;
  }
  return 0;
}
