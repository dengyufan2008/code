#include <fstream>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

int t, n, m, d;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> d;
    if (n == 1) {
      cout << min(m, d) << '\n';
      for (int i = 1; i <= m; i++) {
        cout << (i - 1) % d + 1 << " \n"[i == m];
      }
    } else if (d == 2) {
      cout << 2 << '\n';
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
          cout << (i + j & 1) + 1 << " \n"[j == m];
        }
      }
    } else {
      cout << 1 << '\n';
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
          cout << 1 << " \n"[j == m];
        }
      }
    }
  }
  return 0;
}
