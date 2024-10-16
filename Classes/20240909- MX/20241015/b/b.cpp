#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 3e5 + 1;
int n;
LL ans, f[12], g[12];  // 21 12 0/1/2

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, j = 0, x; i <= n; i++) {
    cin >> x;
    if (!x) {
      ans += 1LL * i * (n - i + 1) - ++j;
    } else {
      j = 0;
    }
    f[0]++;
    g[0] = f[0], g[1] = f[1], g[2] = f[2];
    g[3] = f[3], g[4] = f[4], g[5] = f[5];
    g[6] = f[6], g[7] = f[7], g[8] = f[8];
    g[9] = f[9], g[10] = f[10], g[11] = f[11];
    if (x == 1) {
      f[0] = 0, f[1] = g[0] + g[1], f[2] = 0;
      f[3] = 0, f[4] = g[3] + g[4], f[5] = 0;
      f[6] = 0, f[7] = g[6] + g[7], f[8] = g[2] + g[8];
      f[9] = 0, f[10] = g[9] + g[10], f[11] = g[5] + g[11];
    } else if (x == 2) {
      f[0] = 0, f[1] = 0, f[2] = g[0] + g[2];
      f[3] = 0, f[4] = g[1] + g[4], f[5] = g[3] + g[5];
      f[6] = 0, f[7] = 0, f[8] = g[6] + g[8];
      f[9] = 0, f[10] = g[7] + g[10], f[11] = g[9] + g[11];
    } else if (x == 3) {
      f[0] = g[0] + g[1] + g[2], f[1] = 0, f[2] = 0;
      f[3] = g[3] + g[4] + g[5], f[4] = 0, f[5] = 0;
      f[6] = g[6] + g[7] + g[8], f[7] = 0, f[8] = 0;
      f[9] = g[9] + g[10] + g[11], f[10] = 0, f[11] = 0;
    }
    ans += (f[0] + f[1] + f[2]);
    ans += (f[3] + f[4] + f[5] + f[6] + f[7] + f[8]) * 2;
    ans += (f[9] + f[10] + f[11]) * 3;
  }
  cout << ans << '\n';
  return 0;
}
