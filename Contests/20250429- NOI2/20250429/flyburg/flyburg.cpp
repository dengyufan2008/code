#include <fstream>

using namespace std;

ifstream cin("flyburg.in");
ofstream cout("flyburg.out");

int t, c, k, n, m;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> c >> k >> t;
  while (t--) {
    cin >> n >> m;
    if (c <= (m + 1 >> 1)) {
      cout << "YES\n";
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
          if ((j & 1) && (j + 1 >> 1) <= c) {
            cout << 1;
          } else {
            cout << 0;
          }
        }
        cout << '\n';
      }
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
