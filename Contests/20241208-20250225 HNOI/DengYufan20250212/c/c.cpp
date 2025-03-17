#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const LL kMaxN = 2e5 + 1, kInf = 1e18;
int n, m, a[kMaxN], b[kMaxN], q[kMaxN];

void Update(LL &x, LL y) { x = min(x, y); }

namespace Sub1 {
const int kMaxN = 101;
LL f[kMaxN][kMaxN][kMaxN];

int main() {
  fill(&f[0][0][1], &f[kMaxN][0][0], kInf);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k <= i; k++) {
        if (j >= 1) {
          Update(f[i][j][k], f[i - 1][j - 1][k] + a[i]);
          if (k >= 1) {
            Update(f[i][j][k], f[i - 1][j - 1][k - 1]);
          }
        }
        Update(f[i][j][k], f[i - 1][j + 1][k] + b[i]);
        if (k >= 1) {
          Update(f[i][j][k], f[i - 1][j + 1][k - 1]);
        }
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << f[n][0][q[i]] << " \n"[i == m];
  }
  return 0;
}
}  // namespace Sub1

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i];
  }
  if (n <= 100 && m <= 100) {
    return Sub1::main();
  }
  return 0;
}
