#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("bracket.in");
ofstream cout("bracket.out");

const LL kMaxN = 5e5 + 1, kMaxM = 19;
LL t, n, ans, lg[kMaxN], a[kMaxM][kMaxN], l[kMaxN];
string s;

LL Min(LL x, LL y) {
  LL l = lg[y - x + 1];
  return min(a[l][x], a[l][y - (1 << l) + 1]);
}

int main() {
  for (LL i = 1, j = 0; i < kMaxN; i++) {
    lg[i] = j;
    if (i == (1 << j + 1)) {
      j++;
    }
  }
  cin >> t >> t;
  while (t--) {
    cin >> s;
    ans = 0, l[0] = 0, n = s.size(), s = '~' + s;
    for (LL i = 1; i <= n; i++) {
      a[0][i] = a[0][i - 1] + (s[i] == '(' ? 1 : -1);
      l[i] = i;
    }
    for (LL i = 1; i < kMaxM; i++) {
      for (LL j = 0; j <= n; j++) {
        a[i][j] = a[i - 1][j];
        if (j + (1 << i - 1) <= n) {
          a[i][j] = min(a[i][j], a[i - 1][j + (1 << i - 1)]);
        }
      }
    }
    sort(l, l + n + 1, [](LL i, LL j) { return a[0][i] < a[0][j] || a[0][i] == a[0][j] && i < j; });
    for (LL i = 0, j; i <= n; i = j) {
      for (j = i; j <= n && a[0][l[i]] == a[0][l[j]] && Min(l[i], l[j]) >= a[0][l[i]]; j++) {
      }
      ans += (j - i) * (j - i - 1) / 2;
    }
    cout << ans << '\n';
  }
  return 0;
}
