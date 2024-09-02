#include <fstream>

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

const int kMod = 998244353;
int t, n;

int Pow(int x, int y) {
  int ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = 1LL * ans * x % kMod;
    }
    x = 1LL * x * x % kMod;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    if (n % 3 == 2) {
      cout << Pow(2, n - 1) << '\n';
    } else {
      cout << Pow(2, n) << '\n';
    }
  }
  return 0;
}
