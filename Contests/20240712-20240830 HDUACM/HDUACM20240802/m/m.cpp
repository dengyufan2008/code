#include <fstream>

using namespace std;

ifstream cin("m.in");
ofstream cout("m.out");

const int kMod = 1e9 + 7;
int t, n;

int Pow(int x, int y = kMod - 2) {
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
    cout << (n - 1 + Pow(n)) % kMod << '\n';
  }
  return 0;
}
