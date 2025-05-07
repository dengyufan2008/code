#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 32, kMaxM = 22, kMod = 998244353, kInf = 1e9;
int n, m, o, b[kMaxN];
LL f[kMaxN][kMaxM][kMaxM][kMaxN * kMaxM * 2];
LL g[kMaxN][kMaxM][kMaxM][kMaxN * kMaxM * 2];
LL pw[kMaxN], ans[kMaxN];

void Update(LL &x, LL y) { x = (x + y) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m, pw[0] = 1;
  for (int i = 1; i <= n; i++) {
    cin >> b[i], pw[i] = pw[i - 1] * m % kMod;
  }
  sort(b + 1, b + n + 1), b[n + 1] = kInf, f[0][0][m + 1][0] = 1;
  for (int i = 1; i <= n + 1; i++) {                     // 正在考虑 (a_i, b_i) 对 \
                                                            最后应当将凸包上所有点都确定
    for (int j = 0; j < i; j++) {                        // 已经加上了 j 个 a_i 的贡献
      for (int l = 0; l <= m; l++) {                     // 钦定 < l 的 a_i 都必须加入 \
                                                            即凸包中 w 代表的点下方第一条直线的斜率
        for (int r = max(l, 1); r <= m + 1; r++) {       // 钦定 >= r 的 a_i 都不能加入 \
                                                            即凸包中 w 代表的点上方第一条直线的斜率
          for (int w = 0; w < kMaxN * kMaxM * 2; w++) {  // 这 j 个 a_i 的和
            LL h = f[j][l][r][w];
            if (h) {
              int _l = l, _r = r, _w = max(w, b[i]);
              if (w <= b[i]) {  // 当前状态已经合法
                _l = 0;         // 可以重新钦定哪些加入
              } else {
                _l = min(l, w - b[i]);  // 更新下方斜率
              }
              if (r <= m) {
                _r = r - _w + w;  // 更新上方斜率
              }
              if (l && !_l) {  // 当前恰好把应当加上贡献的都加完了
                Update(ans[j], w * h % kMod * pw[n - i + 1]);
              }
              if (i <= n && _r > 0) {           // w 代表的点未被 b_i 删去, 则可以转移
                for (int x = 1; x < _l; x++) {  // 枚举当前 a_i 的值
                  Update(g[j + 1][_l][_r][_w + x], h);
                }
                for (int x = max(_l, 1); x < _r; x++) {
                  Update(g[j][_l][x][_w], h), Update(g[j + 1][x][_r][_w + x], h);
                }
                for (int x = _r; x <= m; x++) {
                  Update(g[j][_l][_r][_w], h);
                }
              }
            }
          }
        }
      }
    }
    for (int j = 0; j <= i; j++) {
      for (int l = 0; l <= m; l++) {
        for (int r = max(l, 1); r <= m + 1; r++) {
          for (int w = 0; w < kMaxN * kMaxM * 2; w++) {
            f[j][l][r][w] = g[j][l][r][w], g[j][l][r][w] = 0;
          }
        }
      }
    }
  }
  cin >> o;
  for (int i = 1, x; i <= o; i++) {
    cin >> x, cout << ans[x] << '\n';
  }
  return 0;
}
