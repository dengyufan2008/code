#include <fstream>
#define LL long long

using namespace std;

ifstream cin("aspect.in");
ofstream cout("aspect.out");

const int kMaxN = 2001, kMod = 998244353;
int n;
LL ans, f[kMaxN][kMaxN], g[kMaxN];
string s;

void Update(LL &x, LL y) { x = (x + y) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> s, f[0][0] = 1;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') {
      for (int j = 0; j <= i; j++) {
        Update(f[i + 1][j], f[i][j] * (i - j + 1));
      }
    } else {
      for (int j = 0; j <= i; j++) {
        Update(f[i + 1][j + 1], f[i][j] * j);
        Update(g[j + 1], f[i][j]);
      }
      for (int j = 1; j <= i; j++) {
        Update(g[j + 1], g[j]);
        Update(f[i + 1][j], g[j]);
        g[j] = 0;
      }
      Update(f[i + 1][i + 1], g[i + 1]);
      g[i + 1] = 0;
    }
  }
  for (int i = 0; i <= n; i++) {
    Update(ans, f[n][i]);
  }
  cout << ans << '\n';
  return 0;
}
