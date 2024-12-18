#include <fstream>
#define LL long long

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

const int kMaxN = 301, kMaxL = 18, kMod = 1e9 + 7;
int n, a[kMaxN];
LL p, q, ans[2][kMaxN][kMaxN];

int Cmp(int x, int y) {
  if (x < y) {
    return 0;
  } else if (x == y) {
    return 1;
  }
  return 2;
}

void Update(LL &x, LL y) { x = (x + y) % kMod; }

void Dp(LL ans[kMaxN][kMaxN], LL x) {
  static int w, d[kMaxL];
  static LL f[kMaxL][kMaxL][3], g[kMaxL][kMaxL][3];  // 0:<d 1:=d 2:>d
  for (w = 0; x; w++) {
    d[w] = x % 10, x /= 10;
  }
  for (int h = 1; h <= n; h++) {
    for (int j = 0; j < w; j++) {
      for (int k = j; k < w; k++) {
        f[j][k][0] = f[j][k][1] = f[j][k][2] = 0;
        g[j][k][0] = g[j][k][1] = g[j][k][2] = 0;
      }
    }
    for (int j = 0; j < w; j++) {
      int o = Cmp(a[h], d[j]);
      f[j][j][o] = g[j][j][o] = 2;
    }
    if (w > 1 || w == 1 && a[h] <= d[0]) {
      ans[h][h] = 2;
    }
    for (int i = h + 1; i <= n; i++) {
      for (int j = 0; j < w; j++) {
        int o = Cmp(a[i], d[j]);
        Update(g[j][j][o], 2);
      }
      for (int j = 0; j < w; j++) {
        for (int k = j; k < w; k++) {
          // 放在低位
          if (j > 0) {
            int o = Cmp(a[i], d[j - 1]);
            Update(g[j - 1][k][0], f[j][k][0]);
            Update(g[j - 1][k][o], f[j][k][1]);
            Update(g[j - 1][k][2], f[j][k][2]);
          }
          // 放在高位
          if (k + 1 < w) {
            if (a[i] != d[k + 1]) {
              int o = Cmp(a[i], d[k + 1]);
              Update(g[j][k + 1][o], f[j][k][0]);
              Update(g[j][k + 1][o], f[j][k][1]);
              Update(g[j][k + 1][o], f[j][k][2]);
            } else {
              Update(g[j][k + 1][0], f[j][k][0]);
              Update(g[j][k + 1][1], f[j][k][1]);
              Update(g[j][k + 1][2], f[j][k][2]);
            }
          }
        }
      }
      for (int j = 0; j < w; j++) {
        for (int k = j; k < w; k++) {
          f[j][k][0] = g[j][k][0];
          f[j][k][1] = g[j][k][1];
          f[j][k][2] = g[j][k][2];
        }
      }
      Update(ans[h][i], f[0][w - 1][0]);
      Update(ans[h][i], f[0][w - 1][1]);
      for (int k = 0; k + 1 < w; k++) {
        Update(ans[h][i], f[0][k][0]);
        Update(ans[h][i], f[0][k][1]);
        Update(ans[h][i], f[0][k][2]);
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> p >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Dp(ans[0], p - 1), Dp(ans[1], q);
  cin >> n;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    cout << (ans[1][x][y] - ans[0][x][y] + kMod) % kMod << '\n';
  }
  return 0;
}
