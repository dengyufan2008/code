#include <cmath>
#include <fstream>

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 19, kInf = 1e9;
int m, ans, f[1 << kMaxN];

int Calc(int x) {
  static int px = 0, pans = 0;
  x = m / x;
  if (px == x) {
    return pans;
  }
  int n = log2(x) / log2(3) + 1, o = 1;
  f[0] = 0, fill(&f[1], &f[1 << n], kInf);
  for (int i = x; i; i /= 2) {
    for (int j = i, r = 0; j; j /= 3, r++) {
      for (int s = 0; s < 1 << n; s++) {
        if (s >> r & 1 ^ 1) {
          int f0 = f[s], f1 = f[s | 1 << r];
          f[s | 1 << r] = min(f0, f1) + 1;
          if (r && (s >> r - 1 & 1)) {
            f[s] = min(f0, f1);
          } else {
            f[s] = f1;
          }
        }
      }
    }
  }
  px = x, pans = kInf;
  for (int s = 0; s < 1 << n; s++) {
    pans = min(pans, f[s]);
  }
  return pans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> m;
  for (int i = 1, j = 5; i <= m; i += 6, j += 6) {
    ans += Calc(i);
    if (j <= m) {
      ans += Calc(j);
    }
  }
  cout << ans << '\n';
  return 0;
}
