#include <iostream>
#define LL long long

using namespace std;

const int kM = 1e9 + 7;
const int kMaxL = 102;

LL a[kMaxL][kMaxL], b[kMaxL][kMaxL], c[kMaxL][kMaxL], n;
int m;

void Mul(LL a[][kMaxL], LL b[][kMaxL]) {
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= m; j++) {
      c[i][j] = 0;
      for (int k = 1; k <= m; k++) {
        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % kM;
      }
    }
  }
}

void Make() {
  for (int i = 1; i <= m; i++) {
    b[i][i] = a[i][m] = a[i + 1][i] = 1;
  }
}

int main() {
  cin >> n >> m;
  Make();
  for (LL i = 1; i <= n; i <<= 1) {
    if (n & i) {
      Mul(b, a);
      copy(&c[0][0], &c[0][0] + kMaxL * kMaxL, &b[0][0]);
    }
    Mul(a, a);
    copy(&c[0][0], &c[0][0] + kMaxL * kMaxL, &a[0][0]);
  }
  cout << b[m][m];
  return 0;
}
