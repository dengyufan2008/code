#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 121, kMod = 1e9 + 7;
int t, n, a[kMaxN], b[kMaxN];
LL f[kMaxN][kMaxN][kMaxN], ans[kMaxN][kMaxN], inv[kMaxN];

bool Init() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    static char c;
    cin >> c;
    b[i] = b[i - 1] + (c == '1');
  }
  if (b[n] == 0) {
    cout << 0 << '\n';
    return 0;
  } else if (b[n] == n) {
    cout << 1 << '\n';
    return 0;
  } else if (a[n] <= 1) {
    cout << 0 << '\n';
    return 0;
  } else if (a[1] >= 1) {
    cout << 1 << '\n';
    return 0;
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      ans[i][j] = 0;
      for (int k = 0; k <= n; k++) {
        f[i][j][k] = 0;
      }
    }
  }
  return 1;
}

void Update(LL &x, LL y) { x = (x + y) % kMod; }

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

void Dp() {
  static LL g[kMaxN][kMaxN][kMaxN], h[kMaxN];  // g 的第一维记 j 是为了 (i, j) 的数组可以在 (i - 1, j) 复用
  for (int i = n; i >= 1; i--) {               // 最大的牌编号是 i, 转移到最大牌编号 < i 的状态, 且途中不能赢
    bool o = i < n && a[i] == a[i + 1];
    for (int j = min(n - a[i] - 1, i - 1); j >= 0; j--) {  // 除去 i 目前还有 j 张
      if (!a[i]) {
        f[i][j][j] = 1;
        continue;
      }
      for (int x = o ? i : n; x >= i - 1; x--) {  // 可以复用则少清空一部分, 下面从较小位置开始转移
        for (int y = j + a[i]; y <= x && y < n; y++) {
          g[j][x][y] = 0;
        }
      }
      for (int z = j + a[i]; z < i; z++) {
        h[z] = 0;
      }
      !o && (g[j][n][j + a[i]] = 1);
      for (int x = o ? i + 1 : n; x >= i; x--) {        // 转移到最大牌编号 <= x 的状态, 且途中不能赢
        for (int y = j + a[i]; y <= x && y < n; y++) {  // 转移后还有 y 张牌
          if (g[j][x][y]) {
            LL p = (y - j) * inv[x - j] % kMod;  // 一张非 j 内的牌在手里的概率
            Update(g[j][x - 1][y], g[j][x][y] * (1 - p + kMod));
            if (x == i && y - 1 == j) {  // 自己转移到自己的特判
              for (int z = j + a[i]; z < x; z++) {
                Update(h[z], g[j][x][y] * p);
              }
            } else {
              for (int z = j + a[i]; z < x; z++) {
                Update(g[j][x - 1][z], g[j][x][y] * p % kMod * f[x][y - 1][z]);
              }
            }
          }
        }
      }
      for (int k = j + a[i]; k < n; k++) {  // 转移后还有 k 张牌
        f[i][j][k] = g[j][i - 1][k] * Pow(1 - h[k] + kMod) % kMod;
      }
    }
  }
}

void CalcAns() {
  ans[0][0] = 1;
  for (int i = 1; i <= n; i++) {       // 手上所有牌编号都 <= i, 且一定持有 s_i = 1 的牌
    for (int j = b[i]; j <= i; j++) {  // 手上共有 j 张牌, 输的概率
      if (b[i - 1] == b[i]) {
        LL p = (j - b[i]) * inv[i - b[i]] % kMod;  // 一张 s_i = 0 的牌在手上的概率
        ans[i][j] = ans[i - 1][j] * (1 - p + kMod) % kMod;
        for (int k = max(b[i - 1], j - 1 + a[i]); k < i; k++) {
          Update(ans[i][j], f[i][j - 1][k] * ans[i - 1][k] % kMod * p);
        }
      } else {
        for (int k = max(b[i - 1], j - 1 + a[i]); k < i; k++) {
          Update(ans[i][j], f[i][j - 1][k] * ans[i - 1][k]);
        }
      }
    }
  }
  cout << (1 - ans[n][b[n]] + kMod) % kMod << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  inv[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    inv[i] = kMod - (kMod / i) * inv[kMod % i] % kMod;
  }
  cin >> t;
  while (t--) {
    Init() ? Dp(), CalcAns() : void();
  }
  return 0;
}
