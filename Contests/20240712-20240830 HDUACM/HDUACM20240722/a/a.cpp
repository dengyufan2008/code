#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

int t, n;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    if (n < 6) {
      for (int i = 2; i <= n + 1; i++) {
        cout << 1 << ' ' << i << '\n';
      }
    } else if (n < 9) {
      for (int i = 2; i <= n - 1; i++) {
        cout << 1 << ' ' << i << '\n';
      }
      cout << 2 << ' ' << 3 << '\n';
      cout << 2 << ' ' << 4 << '\n';
    } else {
      for (int i = 1; i <= 3; i++) {
        for (int j = i + 1; j <= n / 3 + 4 - i; j++) {
          cout << i << ' ' << j << '\n';
        }
        if (i == 1) {
          for (int j = 1; j <= n % 3; j++) {
            cout << 1 << ' ' << n / 3 + 3 + j << '\n';
          }
        }
      }
    }
  }
  return 0;
}
