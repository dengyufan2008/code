#include <fstream>
#define LL long long

using namespace std;

ifstream cin("knapsack.in");
ofstream cout("knapsack.out");

const LL kMaxN = 2e5 + 1, kMod = 500, kInf = 1e18;
LL p, m, u, z, al, ar, dl, dr, ql, qr, qm, a[kMaxN][2], d[kMaxN][2], q[kMaxN][kMod];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> p >> m >> u;
  al = ql = 1, qm = qr = 2;
  fill(&q[qm - 1][1], &q[qm - 1][p], -kInf);
  fill(&q[qm][1], &q[qm][p], -kInf);
  for (LL i = 1, o, x, y; i <= m; i++) {
    cin >> o;
    if (o == 1) {
      cin >> x >> y;
      if (u) {
        x ^= z, y ^= z;
      }
      x %= p, ar++, a[ar][0] = x, a[ar][1] = y, qr++;
      for (LL j = 0; j < p; j++) {
        LL t = q[qr - 1][(j - x + p) % p];
        q[qr][j] = q[qr - 1][j];
        if (t > -kInf) {
          q[qr][j] = max(q[qr][j], t + y);
        }
      }
    } else if (o == 2) {
      al++, ql++;
      if (ql == qm) {
        ql = 1, qm = qr = ar - al + 3;
        q[qm - 1][0] = 0, fill(&q[qm - 1][1], &q[qm - 1][p], -kInf);
        q[qm][0] = 0, fill(&q[qm][1], &q[qm][p], -kInf);
        for (LL j = qm - 2; j >= ql; j--) {
          for (LL k = 0; k < p; k++) {
            LL t = q[j + 1][(k - a[j - 1 + al][0] + p) % p];
            q[j][k] = q[j + 1][k];
            if (t > -kInf) {
              q[j][k] = max(q[j][k], t + a[j - 1 + al][1]);
            }
          }
        }
        for (LL j = qm + 1; j <= qr; j++) {
          for (LL k = 0; k < p; k++) {
            LL t = q[j - 1][(k - a[j - 3 + al][0] + p) % p];
            q[j][k] = q[j - 1][k];
            if (t > -kInf) {
              q[j][k] = max(q[j][k], t + a[j - 3 + al][1]);
            }
          }
        }
      }
    } else {
      cin >> x >> y;
      if (u) {
        x ^= z, y ^= z;
      }
      LL ans = -kInf, t = 0;
      x %= p, y %= p, dl = 1, dr = 0;
      for (LL j = y; j != x; j = (j - 1 + p) % p) {
        t++;
        for (; dr >= dl && d[dr][0] <= q[qr][j]; dr--) {
        }
        dr++, d[dr][0] = q[qr][j], d[dr][1] = t;
      }
      for (LL j = 0, l = x, r = y; j < p; j++, l = (l - 1 + p) % p, r = (r - 1 + p) % p) {
        t++;
        for (; dr >= dl && d[dr][0] <= q[qr][l]; dr--) {
        }
        dr++, d[dr][0] = q[qr][l], d[dr][1] = t;
        for (; dl <= dr && d[dl][1] <= t - (r - l + p) % p - 1; dl++) {
        }
        if (q[ql][j] > -kInf && d[dl][0] > -kInf) {
          ans = max(ans, q[ql][j] + d[dl][0]);
        }
      }
      cout << (ans == -kInf ? -1 : z = ans) << '\n';
    }
  }
  return 0;
}
