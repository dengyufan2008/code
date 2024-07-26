#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e6 + 1, kMod = 998244353;
int n, f[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    f[i] = (f[i] + 1) % kMod;
    for (int j = i + 1; j <= n; j += i + 1) {
      f[j] = (f[j] + f[i]) % kMod;
    }
    cout << f[i] << " \n"[i == n];
  }
  return 0;
}
