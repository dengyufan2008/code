#include <fstream>
#define LL long long

using namespace std;

ifstream cin("z.in");
ofstream cout("z.out");

int t;
LL n, m, p, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  for (int o = 1; o <= t; o++) {
    cin >> n >> m >> p;
    ans = ((n - m - 1) * (n - m - 1) + (m + 1) * (n - m)) % p;
    for (int i = 2; i <= m; i++) {
      ans = ans * i % p;
    }
    cout << "Case #" << o << ": " << ans << '\n';
  }
  return 0;
}
