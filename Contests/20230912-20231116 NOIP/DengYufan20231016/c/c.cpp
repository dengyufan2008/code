#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const LL kMaxN = 501;
LL n, q, s1[kMaxN][kMaxN], s2[kMaxN][kMaxN], c[kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> q;
  for (LL t = 1, o, x, y; t <= q; t++) {
    cin >> o >> x >> y;
    x > y ? swap(x, y) : (void)0;
    if (o == 1) {
      for (LL i = y; i <= n; i++) {
        s1[x][i] += y - x;
        s2[x][i] += x + y;
        c[x][i]++;
      }
    } else {
      LL mid = x + y >> 1, gap = y - x >> 1, ans = 0;
      for (LL i = 1; i <= x; i++) {
        ans += s1[i][mid] + (c[i][y] - c[i][mid]) * (x + y) - (s2[i][y] - s2[i][mid]) + (c[i][n] - c[i][y]) * (x - y) + (s1[i][n] - s1[i][y]);
      }
      for (LL i = x + 1; i <= mid; i++) {
        ans += s1[i][i + gap] + (c[i][y] - c[i][i + gap]) * (y - x) - (s1[i][y] - s1[i][i + gap]) - (c[i][n] - c[i][y]) * (x + y) + (s2[i][n] - s2[i][y]);
      }
      for (LL i = mid + 1; i <= n; i++) {
        ans += s1[i][n];
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
