#include <iostream>

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

int a, b;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> a >> b;
  if (b == 0 && a == 0) {
    cout << 1 << '\n';
  } else if (b == 0 && a >= 2 && a != 3) {
    cout << a + (a != 2) << '\n';
    for (int i = 2; i <= a + (a != 2); i++) {
      cout << 1 << ' ' << i << '\n';
    }
  } else if (a >= b + 2 && a != b + 3) {
    cout << a + b + (b != 1 || a >= b + 4) << '\n';
    for (int i = 1; i < b; i++) {
      cout << i << ' ' << i + 1 << '\n';
    }
    cout << 1 << ' ' << b + 1 << '\n';
    cout << 1 << ' ' << b + 2 << '\n';
    for (int i = 2; i < b; i++) {
      cout << i << ' ' << b + i + 1 << '\n';
    }
    if (b == 1) {
      cout << b + 3 << ' ' << 1 << '\n';
      for (int i = b + 3; i <= a + (a >= b + 4); i++) {
        cout << b + 3 << ' ' << i + 1 << '\n';
      }
    } else {
      for (int i = b + 3; i <= a + 1; i++) {
        cout << b + 2 << ' ' << i + b - 2 << '\n';
      }
      cout << b << ' ' << a + b << '\n';
      cout << b << ' ' << a + b + 1 << '\n';
    }
  } else {
    cout << 0 << '\n';
  }
  return 0;
}
