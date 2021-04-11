#include <iostream>
#define LL long long

using namespace std;

const int kMax = 1e9 + 7;

int a[101][101], b[101][101], c[101][101],
    n, m, k;

void Mul(int a[101][101], int b[101][101]) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      c[i][j] = 0;
      for (int l = 1; l <= k; l++) {
        c[i][j] = (c[i][j] + a[i][l] * b[l][j]) % kMax;
      }
    }
  }
}

int main() {
  cin >> n >> k >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> b[i][j];
    }
  }
  Mul(a, b);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cout << c[i][j] << " ";
    }
    cout << "\n";
  }
  return 0;
}
