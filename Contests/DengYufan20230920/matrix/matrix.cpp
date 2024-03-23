#include <chrono>
#include <fstream>
#include <random>
#include <set>
#define LL long long

using namespace std;

ifstream cin("matrix.in");
ofstream cout("matrix.out");

const LL kMaxN = 2001, kR[9] = {-1, 0, 1, 2, -1, 3, 4, 5, -1};
LL n, m, k, w[kMaxN], s[kMaxN][kMaxN], a[kMaxN][kMaxN][4], b[kMaxN][kMaxN];
char o;
set<LL> st[6];
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k;
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= n; j++) {
      cin >> a[i][j][2];
      a[i][j][0] = i, a[i][j][1] = j;
    }
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= n; j++) {
      cin >> a[i][j][3];
    }
  }
  for (LL p = 0; p < 3; p++) {
    for (LL q = 0; q < 3; q++) {
      if (p != q) {
        w[0] = 0;
        for (LL i = 1; i <= n; i++) {
          w[i] = Rand(), w[0] += w[i];
          for (LL j = 1; j <= n; j++) {
            b[a[i][j][p]][a[i][j][q]] = a[i][j][3], s[i][j] = 0;
          }
        }
        for (LL i = 1; i <= n; i++) {
          for (LL j = 1; j <= n; j++) {
            s[j][b[i][j]] += w[i];
          }
        }
        for (LL i = 1; i <= n; i++) {
          LL t = 0;
          for (LL j = 1; j <= n; j++) {
            t += s[j][b[i][j]];
          }
          if (t - w[i] * n == (w[0] - w[i]) * m) {
            st[kR[p * 3 + q]].insert(i);
          }
        }
      }
    }
  }
  for (LL i = 1, t, p = 0, q = 1, x = 0, y = 0, z = 0; i <= k; i++) {
    cin >> o;
    if (o == 'X') {
      cin >> t;
      y = (y + t) % n;
    } else if (o == 'Y') {
      cin >> t;
      x = (x + t) % n;
    } else if (o == 'I') {
      q ^= p ^ 3, swap(y, z);
    } else if (o == 'C') {
      p ^= q ^ 3, swap(x, z);
    } else {
      auto r = st[kR[p * 3 + q]].upper_bound(n - x);
      if (r != st[kR[p * 3 + q]].end()) {
        cout << (*r + x - 1) % n + 1 << '\n';
        continue;
      }
      r = st[kR[p * 3 + q]].upper_bound(0);
      if (r != st[kR[p * 3 + q]].end()) {
        cout << (*r + x - 1) % n + 1 << '\n';
        continue;
      }
      cout << -1 << '\n';
    }
  }
  return 0;
}
