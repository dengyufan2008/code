#include <fstream>
#define LL long long

using namespace std;

ifstream cin("emo.in");
ofstream cout("emo.out");

int n;
LL m, p;

namespace Sub1 {
LL a[2][2], b[2][2];

void Mul(LL a[2][2], LL b[2][2]) {
  LL c[2][2] = {};
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      c[i][j] = (a[i][0] * b[0][j] + a[i][1] * b[1][j]) % p;
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a[i][j] = c[i][j];
    }
  }
}

int main() {
  a[0][0] = a[1][1] = 1;
  b[0][0] = b[0][1] = 1;
  b[1][0] = 1;
  for (LL i = 1; i <= m; i <<= 1) {
    if (i & m) {
      Mul(a, b);
    }
    Mul(b, b);
  }
  cout << (a[1][0] + a[1][1]) % p << '\n';
  return 0;
}
}  // namespace Sub1
namespace Sub2 {
LL a[4][4], b[4][4];

void Mul(LL a[4][4], LL b[4][4]) {
  LL c[4][4] = {};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % p;
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      a[i][j] = c[i][j];
    }
  }
}

int main() {
  a[0][0] = a[1][1] = a[2][2] = a[3][3] = 1;
  b[0][0] = b[0][1] = b[0][2] = b[0][3] = 1;
  b[1][0] = b[1][2] = b[1][3] = 1;
  b[2][0] = b[2][1] = b[2][3] = 1;
  b[3][0] = b[3][3] = 1;
  for (LL i = 1; i <= m; i <<= 1) {
    if (i & m) {
      Mul(a, b);
    }
    Mul(b, b);
  }
  cout << (a[3][0] + a[3][1] + a[3][2] + a[3][3]) % p << '\n';
  return 0;
}
}  // namespace Sub2

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> p;
  if (n == 1) {
    return Sub1::main();
  } else if (n == 2) {
    return Sub2::main();
  }
}
