#include <fstream>
#define LL long long

using namespace std;

ifstream cin("tree.in");
ofstream cout("tree.out");

const LL kMaxN = 1e6 + 1, kMod = 1e9 + 7;
LL n, ans, nt[kMaxN], p[kMaxN] = {1};
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s;
  n = s.size();
  for (LL i = 1; i <= n; i++) {
    p[i] = p[i - 1] * 26 % kMod;
  }
  nt[0] = -1;
  for (LL i = 1, j; i < n; i++) {
    for (j = nt[i - 1]; j >= 0 && s[j + 1] != s[i]; j = nt[j]) {
    }
    nt[i] = s[j + 1] == s[i] ? j + 1 : -1;
  }
  for (LL i = 0; i < n; i++) {
    if (nt[i] == -1) {
      ans = (ans + p[n - i - 1]) % kMod;
    }
  }
  cout << (p[n] - ans + kMod) % kMod;
  return 0;
}
