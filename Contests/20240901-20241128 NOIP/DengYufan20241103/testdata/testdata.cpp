#include <fstream>
#define LL long long

using namespace std;

ifstream cin("testdata.in");
ofstream cout("testdata.out");

const int kMod = 1e9 + 7;
int t;
LL n, m, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> m >> n;
    if (m == 1) {
      cout << 0 << '\n';
    } else {
      for (ans = 1; ans <= m; ans <<= 1) {
      }
      ans = (ans - 1) % kMod;
      n = (n >> 1) * (n + 1 >> 1) % kMod;
      cout << n * ans % kMod << '\n';
    }
  }
  return 0;
}
