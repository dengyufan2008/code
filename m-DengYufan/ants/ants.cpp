#include <iostream>
#define LL long long

using namespace std;

const int kMod = 1e7;
int t, a, s, b, ans, d[1001], f[1001][100001];

int main() {
  // freopen("ants.in", "r", stdin);
  // freopen("ants.out", "w", stdout);
  cin >> t >> a >> s >> b;
  for (int i = 1, x; i <= a; i++) {
    cin >> x;
    d[x]++;
  }
  for (int i = 0; i <= d[1]; i++) {
    f[1][i] = 1;
  }
  for (int i = 1; i < t; i++) {
    for (int j = 0; j <= a; j++) {
      for (int k = 0; k <= min(a - j, d[i + 1]); k++) {
        f[i + 1][j + k] = (f[i + 1][j + k] + f[i][j]) % kMod;
      }
    }
  }
  for (int i = s; i <= b; i++) {
    ans += f[t][i];
  }
  cout << ans << endl;
  return 0;
}
