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
  int n = log2(x) / log2(3) + 1, nn = 1 << n, o = 1;
  f[0] = 0, fill(&f[1], &f[nn], kInf);
  for (int i = x; i; i /= 2) {
    for (int j = i, r = 0, rr = 1; j; j /= 3, r++, rr <<= 1) {
      for (int s = rr; s < nn; s = s + 1 | rr) {
        f[s ^ rr] = min(f[s ^ rr], f[s]);
        if (s >> r - 1 & 1) {
          f[s] = f[s ^ rr] + 1;
        } else {
          swap(f[s], ++f[s ^ rr]);
        }
      }
    }
  }
  px = x, pans = kInf;
  for (int s = 0; s < nn; s++) {
    pans = min(pans, f[s]);
  }
  return pans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> m;
  for (int i = 1; i <= m; i += 6) {
    ans += Calc(i);
    if (i + 4 <= m) {
      ans += Calc(i + 4);
    }
  }
  cout << ans << '\n';
  return 0;
}
