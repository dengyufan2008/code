#include <fstream>

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

int t, n, m, h, d;

char C(int x) {
  if (x < 0) {
    return ' ';
  } else {
    return char('A' + x % 5);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> h >> d;
    if (d >= m) {
      for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
          if ((i == 0 || i == n + 1) && (j == 0 || j == m + 1)) {
            cout << '+';
          } else if (i == 0 || i == n + 1) {
            cout << '-';
          } else if (j == 0 || j == m + 1) {
            cout << '|';
          } else {
            cout << '.';
          }
        }
        cout << '\n';
      }
    } else if (d > h % m) {
      for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
          if ((i == 0 || i == n + 1) && (j == 0 || j == m + 1)) {
            cout << '+';
          } else if (i == 0 || i == n + 1) {
            cout << '-';
          } else if (j == 0 || j == m + 1) {
            cout << '|';
          } else if (j <= h % m || j > m - d + h % m) {
            cout << '.';
          } else {
            cout << C(h / m - 1);
          }
        }
        cout << '\n';
      }
    } else {
      for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
          if ((i == 0 || i == n + 1) && (j == 0 || j == m + 1)) {
            cout << '+';
          } else if (i == 0 || i == n + 1) {
            cout << '-';
          } else if (j == 0 || j == m + 1) {
            cout << '|';
          } else if (j <= h % m - d) {
            cout << C(h / m);
          } else if (j <= h % m) {
            cout << '.';
          } else {
            cout << C(h / m - 1);
          }
        }
        cout << '\n';
      }
    }
  }
  return 0;
}
