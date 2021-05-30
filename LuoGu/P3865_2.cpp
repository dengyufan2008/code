#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, l, r, d, ans, f[100001][20], v[100001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, j = 0; i <= n; i++) {
    cin >> f[i][0];          // 读入单位区间的最大值
    j += i == 1 << (j + 1);  // 最高1位变化
    v[i] = j;                // 记录最高1位的位权
  }
  for (int j = 1; j < 20; j++) {                              // 枚举幂
    for (int i = 1; i + (1 << j) <= n + 1; i++) {                // 枚举左界
      f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);  // 计算相应区间的最值
    }
  }
  while (m--) {  // 处理查询
    cin >> l >> r;
    d = v[r - l + 1];  // 求出覆盖区间的幂
    cout << max(f[l][d], f[r - (1 << d) + 1][d]) << '\n';
  }
  return 0;
}
