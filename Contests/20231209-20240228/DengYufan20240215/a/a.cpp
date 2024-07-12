#include <iostream>
#define LL long long

using namespace std;

const int kMaxN = 11, kMod = 998244353;
int n, m;
LL ans, a[kMaxN][kMaxN], b[kMaxN][kMaxN];
string s;

void Mul(LL a[kMaxN][kMaxN], LL b[kMaxN][kMaxN]) {
  LL c[kMaxN][kMaxN] = {};
  for (int i = 0; i < kMaxN; i++) {
    for (int j = 0; j < kMaxN; j++) {
      for (int k = 0; k < kMaxN; k++) {
        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % kMod;
      }
    }
  }
  copy(&c[0][0], &c[kMaxN][0], &a[0][0]);
}

void Mul(LL a[kMaxN][kMaxN], int x) {
  for (int i = 0; i < kMaxN; i++) {
    LL s = 0;
    for (int j = 0; j < kMaxN; j++) {
      s = (s + a[i][j]) % kMod;
    }
    a[i][x] = s;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 0; i < kMaxN; i++) {
    a[i][i] = 1;
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> m >> s;
    m--, copy(&a[0][0], &a[kMaxN][0], &b[0][0]);
    for (int j = 1; j <= m; j <<= 1) {
      if (j & m) {
        Mul(a, b);
      }
      Mul(b, b);
    }
    for (int j = 0; j < s.size(); j++) {
      Mul(a, s[j] - 47);
    }
  }
  for (int i = 1; i < kMaxN; i++) {
    ans = (ans + a[0][i]) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
