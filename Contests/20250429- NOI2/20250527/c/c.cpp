#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 101, kMod = 998244353;
int n, m, s, t;
LL a[kMaxN][kMaxN], w[kMaxN][kMaxN];

void Mul(LL a[kMaxN][kMaxN], LL b[kMaxN][kMaxN]) {
  static LL c[kMaxN][kMaxN];
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % kMod;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      a[i][j] = c[i][j], c[i][j] = 0;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> s >> t;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    a[x][y] = a[y][x] = 1;
  }
  for (int i = 1; i <= n; i++) {
    a[i][i] = 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      w[i][j] = a[i][j];
    }
  }
  m--;
  for (int i = 1; i <= m; i <<= 1) {
    if (i & m) {
      Mul(a, w);
    }
    Mul(w, w);
  }
  cout << a[s][t] << '\n';
  return 0;
}
