#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

__int128_t n, m, ans, a[81], f[81][81];

void Input(__int128_t &x) {
  char c = ' ';
  x = 0;
  while (c < '0' || c > '9') {
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
}

void Output(__int128_t x) {
  if (x / 10) {
    Output(x / 10);
  }
  putchar(x % 10 + '0');
}

int main() {
  Input(n), Input(m);
  while (n--) {
    fill(&f[0][0], &f[80][80] + 1, 0);
    for (__int128_t i = 1; i <= m; i++) {
      Input(a[i]);
      f[i][i] = a[i] * 2;
    }
    for (__int128_t i = 2; i <= m; i++) {
      for (__int128_t j = 1, k; (k = j + i - 1) <= m; j++) {
        f[j][k] = max(f[j + 1][k] * 2 + a[j] * 2, f[j][k - 1] * 2 + a[k] * 2);
      }
    }
    ans += f[1][m];
  }
  Output(ans);
  // cout << endl << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
