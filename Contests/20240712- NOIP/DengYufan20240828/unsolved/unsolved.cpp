#include <fstream>
#define LL long long
#define LLL __int128_t

using namespace std;

ifstream cin("unsolved.in");
ofstream cout("unsolved.out");

const int kMaxN = 1e7 + 1;
int n, p, q, ans;
LL s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> p >> q >> s;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    ans += (LLL)s * p < (LLL)x * q;
    s += x;
  }
  cout << ans << '\n';
  return 0;
}
