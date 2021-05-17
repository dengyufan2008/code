#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 102;
const double kZ = 1e-6;  // 判断实数0

struct E {          // 方程
  int p;            // 主元列
  double a[kMaxN];  // 系数
} e[kMaxN];
double x[kMaxN];  // 解
int n;

bool Find(int s, int p) {         // 找到s行开始p列的主元
  for (int i = s; i <= n; i++) {  // 从s行开始查找
    if (abs(e[i].a[p]) > kZ) {    // p列不为0
      swap(e[s], e[i]);           // 交换行
      return 1;
    }
  }
  return 0;
}

bool Calc() {                                    // 高斯消元求方程解
  int i = 1, p = 0, b = 0;                       // 初始化行列和唯一解标记
  for (; i <= n; i++) {                          // 消完所有行
    for (p++; p <= n + 1 && !Find(i, p); p++) {  // 寻找最近拥有主元的列
      b = 1;                                     // 出现自由变量，标记多解
    }
    if (p > n) {  // 列已消完
      break;
    }
    e[i].p = p;                     // 记录主元列
    for (int j = 1; j <= n; j++) {  // 将其他方程的主元列消成0
      if (i != j) {
        for (int k = n + 1; k >= p; k--) {  // 注意要最后消主元列
          e[j].a[k] -= e[i].a[k] / e[i].a[p] * e[j].a[p];
        }
      }
    }
  }
  for (i--; i; i--) {  // 求解
    x[e[i].p] = e[i].a[n + 1] / e[i].a[e[i].p];
  }
  return p != n + 1 && !b;  // 有解且非多解
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n + 1; j++) {
      cin >> e[i].a[j];
    }
  }
  if (!Calc()) {
    cout << "No Solution" << endl;
  } else {
    cout << fixed << setprecision(2);
    for (int i = 1; i <= n; i++) {
      cout << x[i] << endl;
    }
  }
  return 0;
}
