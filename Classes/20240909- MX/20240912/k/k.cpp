#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

const LL kMaxN = 10001, kInf = 1e18;
int n, m, v, a[kMaxN];
LL ans, s[kMaxN], f[kMaxN][kMaxN * 2];

void Update(LL &x, LL y) { x = min(x, y); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, v = (n + m - 1) / m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  if (n <= m) {
    cout << a[n] << '\n';
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + a[i];
  }
  fill(&f[0][0], &f[kMaxN][0], kInf), f[n][1 + kMaxN] = 0;
  for (int i = n; i >= m; i--) {
    for (int j = -v; j <= v; j++) {
      if (f[i][j + kMaxN] < kInf) {
        for (int k = 2; k <= m && j + k - 1 <= v; k++) {
          Update(f[i][j + k - 1 + kMaxN], f[i][j + kMaxN] + a[k] + s[k]);
        }
        for (int k = max(j + m - v - 1, 1); k + (j == -v) <= m && k <= i; k++) {
          Update(f[i - k][j + m - k - 1 + kMaxN], f[i][j + kMaxN] + a[i] + s[m - k]);
        }
      }
    }
  }
  ans = f[0][kMaxN];
  for (int i = 1; i <= m; i++) {
    Update(ans, f[i][1 + kMaxN] + a[i]);
  }
  cout << ans << '\n';
  return 0;
}
