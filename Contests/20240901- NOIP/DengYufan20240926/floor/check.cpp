#include <fstream>
#define LL long long

using namespace std;

ifstream cin("floor.ans");
ofstream cout("floor.res");

const int kMaxN = 11, kMod = 998244353;
const LL kAns[] = {998244330, 332748146, 499122170, 166374059, 0, 0, 332748146, 998244321, 499122182, 0, 0, 499122170, 499122182, 0, 0, 166374059, 0, 0, 0, 0, 0};

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
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
  for (int i = 1; i < kMaxN; i++) {
    for (int j = 1; j < kMaxN; j++) {
      int ans, c = 0;
      LL chick = 0;
      cin >> ans;
      for (int p = 0; p <= 5; p++) {
        for (int q = 0; q <= 5; q++) {
          if (p + q <= 5) {
            int w = Pow(i, p) * Pow(j, q);
            chick = (chick + kAns[c++] * w) % kMod;
          }
        }
      }
      if (ans != chick) {
        cout << i << ' ' << j << ' ' << ans << ' ' << chick << '\n';
      }
    }
  }
  cout << "done.\n";
  return 0;
}
