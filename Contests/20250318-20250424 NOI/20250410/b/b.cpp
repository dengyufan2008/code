#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 301, kMod = 998244353;
int n, m, a[kMaxN];
LL ans;

void Update(LL &x, LL y) { x = (x + y) % kMod; }

// 从 T 变为 S, 最终 0 的数量需要不超过 S 未匹配的数的数量
void Dp1() {
  LL f[kMaxN][kMaxN];  // 考虑完了 > i 的数, <= i 的数各添加了 j 个, S 中还有 k 个 > i 的数未匹配
  f[0][0] = 1;
  for (int i = m; i >= 1; i--) {
    static LL g[kMaxN][kMaxN];
    for (int j = 0; i * j <= n; j++) {
      for (int k = 0; k <= n; k++) {
        g[j][k] = 0;
      }
    }
    for (int j = 0; (i + 1) * j <= n; j++) {
      for (int k = 0; k <= n; k++) {
        if (f[j][k]) {
          for (int l = j; i * (j + l - a[i]) <= n; l++) {  // T 中原本有 l-j 个 i
            if (l < a[i]) {
              Update(g[j][k + a[i] - l], f[j][k]);
            } else {
              Update(g[j + l - a[i]][k], f[j][k]);
            }
          }
        }
      }
    }
    for (int j = 0; i * j <= n; j++) {
      for (int k = 0; k <= n; k++) {
        f[j][k] = g[j][k];
      }
    }
  }
  ans--;  // T 非空
  for (int j = 0; j <= n; j++) {
    for (int k = j; k <= n; k++) {
      Update(ans, f[j][k] * (k - j + 1));  // 最多还能填 k-j 个 0
    }
  }
}

// 减去 T 是 S 的子集且不合法的方案数
void Dp2() {
  static LL f[kMaxN];
  for (int i = 1; i <= m; i++) {  // 枚举 T 的最小值
    if (!a[i]) {
      continue;
    }
    int c = 1, s = 0, w = 0;
    for (int j = i - 1; j >= 1 && c <= n; j--) {
      if (c < a[j]) {
        s += a[j] - c;
      } else {
        c += c - a[j];
      }
    }
    for (int j = i; j <= m; j++) {
      w += a[j];
    }
    f[0] = 1, fill(&f[1], &f[n] + 1, 0);
    for (int j = i; j <= m; j++) {
      static LL g[kMaxN];
      for (int k = 0; k <= n; k++) {
        if (f[k]) {
          for (int l = 0; l <= a[j] - (j == i); l++) {  // T 里填 l 个 j
            Update(g[k + l], f[k]);
          }
        }
      }
      for (int k = 0; k <= n; k++) {
        f[k] = g[k], g[k] = 0;
      }
    }
    for (int k = max(s + w - c + 1, 0); k <= n; k++) {
      Update(ans, -f[k]);
    }
  }
  ans += !a[1];  // 会把 S=T 算作不合法
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n, m = n;
  for (int i = 1, x; i <= n; i++) {
    cin >> x, x += !x, a[x]++, m = max(m, x);
  }
  Dp1(), Dp2(), cout << (ans + kMod) % kMod << '\n';
  return 0;
}
