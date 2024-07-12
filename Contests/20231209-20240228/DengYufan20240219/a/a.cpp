#include <iostream>

using namespace std;

const int kMaxN = 120001;
int n, f[kMaxN];

void Print(int x, int n) {
  if (n == 1) {
    return;
  }
  int a = n - 1 >> 1, b = n + 1 >> 1, w = n & 1 ? a : b;
  for (int i = 1; i <= w; i++) {
    cout << x << ' ' << x + b << '\n';
  }
  Print(x, b);
  for (int i = 1; i <= b; i++) {
    cout << x + b << ' ' << x + n << '\n';
  }
  Print(x + b, w);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  if (n == 0) {
    cout << 0 << '\n';
    return 0;
  }
  for (int i = 2; i <= n; i++) {
    if (i & 1) {
      f[i] = i + f[i - 1 >> 1] + f[i + 1 >> 1];
    } else {
      f[i] = i + (f[i >> 1] << 1);
    }
  }
  cout << f[n] + 1 << '\n';
  cout << 0 << ' ' << n << '\n';
  Print(0, n);
  return 0;
}
