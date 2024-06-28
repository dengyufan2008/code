#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 10001;
int t, n;
LL a[kMaxN];
short f[kMaxN][kMaxN];
bool l[kMaxN][kMaxN], r[kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  f[1][n] = 1, cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
      for (int j = 1, k; (k = j + i - 1) <= n; j++) {
        f[k][j] = 0;
      }
    }
    for (int i = n; i > 1; i--) {
      for (int j = 1, k; (k = j + i - 1) <= n; j++) {
        l[k][j] = r[k][j] = 1;
      }
    }
    for (int i = n; i > 1; i--) {
      for (int j = 1, k; (k = j + i - 1) <= n; j++) {
        ;
      }
    }
  }
  return 0;
}
