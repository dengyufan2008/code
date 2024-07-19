#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const LL kMaxN = 1001, kInf = 1e18;
int t, n, m, a[kMaxN][5];
LL f[kMaxN * 4];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= 4; j++) {
        cin >> a[i][j];
      }
    }
    fill(&f[1], &f[m] + 1, kInf);
    for (int i = 1; i <= n; i++) {
      for (int j = m; j >= 1; j--) {
        for (int k = 1; k <= 4; k++) {
          f[j] = min(f[j], f[j - k] + a[i][k]);
        }
      }
    }
    cout << f[m] << '\n';
  }
  return 0;
}
