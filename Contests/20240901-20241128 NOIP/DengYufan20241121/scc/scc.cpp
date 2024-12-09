#include <fstream>
#define LL long long

using namespace std;

ifstream cin("scc.in");
ofstream cout("scc.out");

const int kMaxN = 1e6 + 1, kMod = 1e9 + 7;
int n, m, a[kMaxN], b[kMaxN];
LL ans, pw[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i] = pw[i - 1] * 2 % kMod;
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    int j = i;
    for (; !b[j]; j = a[j]) {
      b[j] = i;
    }
    if (b[j] == i) {
      int c = 1;
      for (int k = a[j]; k != j; k = a[k]) {
        c++;
      }
      m += c, ans = (ans + (c * (pw[c - 1] - 1) + 1) % kMod * pw[n - c]) % kMod;
    }
  }
  ans = (ans + (n - m) * pw[n - 1] % kMod) % kMod;
  cout << ans << '\n';
  return 0;
}
