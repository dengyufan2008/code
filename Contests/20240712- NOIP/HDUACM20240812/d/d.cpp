#include <fstream>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

int t, n, m, a, b;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> a >> b;
    n > m ? swap(n, m), swap(a, b) : void();
    if (n <= 2) {
      cout << n * m << '\n';
    } else if (a == 1 && b == 1 || a == 1 && b == m || a == n && b == 1 || a == n && b == m) {
      cout << n * 2 + m * 2 - 4 << '\n';
    } else if (a == 1 || a == n) {
      cout << n * 3 + m * 2 - 6 << '\n';
    } else {
      cout << n * 2 + m * 3 - 6 << '\n';
    }
  }
  return 0;
}
