#include <fstream>
#define LL long long

using namespace std;

ifstream cin("l.in");
ofstream cout("l.out");

const int kMod = 998244353;
int t, n;

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
  cin >> t;
  while (t--) {
    cin >> n;
    cout << Pow(2, n - (n % 3 == 2)) << '\n';
  }
  return 0;
}
