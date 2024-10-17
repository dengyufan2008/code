#include <fstream>
#define LL long long

using namespace std;

ifstream cin("matrix.in");
ofstream cout("matrix.out");

const int kMaxN = 1001;
int t, n, m, k;
LL a[kMaxN][kMaxN];
bool ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        static int x;
        cin >> x;
        a[(i - 1) % k + 1][(j - 1) % k + 1] += x;
      }
    }
    for (int i = 1; i <= k; i++) {
      for (int j = k; j >= 1; j--) {
        a[i][j] -= a[i][1];
      }
    }
    for (int i = 2; i <= k; i++) {
      for (int j = k; j >= 1; j--) {
        a[j][i] -= a[1][i];
      }
    }
    ans = 1;
    for (int i = 1; i <= k; i++) {
      for (int j = 1; j <= k; j++) {
        ans &= !a[i][j], a[i][j] = 0;
      }
    }
    cout << (ans ? "YES\n" : "NO\n");
  }
  return 0;
}
