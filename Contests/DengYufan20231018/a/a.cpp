#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const LL kMaxN = 1e5 + 1, kMaxL = 3, kInf = 1e18;
LL n, a[kMaxN], f[kMaxN][kMaxL];
bool b[kMaxN];
char c;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> a[1];
  for (int i = 2; i <= n; i++) {
    cin >> c >> a[i];
    (c == '-') && (b[i] = 1) && (a[i] = -a[i]);
  }
  fill(&f[0][1], &f[kMaxN][0], -kInf);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < kMaxL; j++) {
      f[i][j] = max(f[i][j], f[i - 1][j] + (j & 1 ? -a[i] : a[i]));
    }
    for (int j = kMaxL - 2; j >= 0; j--) {
      f[i][j] = max(f[i][j], f[i][j + 1]);
    }
    if (b[i]) {
      for (int j = 1; j < kMaxL; j++) {
        f[i][j] = max(f[i][j], f[i - 1][j - 1] + (j & 1 ? a[i] : -a[i]));
      }
    }
  }
  cout << f[n][0];
  return 0;
}
