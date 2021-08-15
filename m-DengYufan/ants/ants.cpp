#include <iostream>
#define LL long long

using namespace std;

const LL kMod = 1e6;
LL t, a, s, b, ans, d[1002], f[2][100002];

int main() {
  freopen("ants.in", "r", stdin);
  freopen("ants.out", "w", stdout);
  cin >> t >> a >> s >> b;
  for (LL i = 1, x; i <= a; i++) {
    cin >> x;
    d[x]++;
  }
  for (LL i = 0; i <= d[1]; i++) {
    f[0][i] = 1;
  }
  for (LL i = 2; i <= t; i++) {
    for (LL j = 0; j <= a; j++) {
      f[1][j] = (f[1][j] + f[0][j]) % kMod, f[1][j + min(a - j, d[i]) + 1] = (f[1][j + min(a - j, d[i]) + 1] - f[0][j] + kMod) % kMod;
    }
    for (LL j = 1; j <= a; j++) {
      f[1][j] = (f[1][j] + f[1][j - 1]) % kMod;
    }
    copy(&f[1][0], &f[1][100000] + 1, &f[0][0]);
    fill(&f[1][0], &f[1][100000] + 1, 0);
  }
  for (LL i = s; i <= b; i++) {
    ans = (ans + f[0][i]) % kMod;
  }
  cout << ans << endl;
  return 0;
}
