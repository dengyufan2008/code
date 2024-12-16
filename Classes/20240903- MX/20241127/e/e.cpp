#include <fstream>
#define LL long long

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 1e6 + 1, kMod = 998244353;
int t, n;
LL g, f[kMaxN];
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 1; i < kMaxN; i++) {
    f[i] = (f[i - 1] + 1) * (f[i - 1] + 1) % kMod;
  }
  cin >> t;
  while (t--) {
    cin >> n >> s;
    if (s[0] == '1') {
      cout << f[n] << '\n';
      continue;
    }
    g = 0;
    for (int i = n - 1; i >= 1; i--) {
      g = (g + 1) * (f[n - i - (s[i] == '0')] + 1) % kMod;
    }
    cout << g << '\n';
  }
  return 0;
}
