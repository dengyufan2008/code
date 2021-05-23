#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxM = 20;
int n, m, ans = 1e9;

bool Check(int l, int v, int r, int h) {  // l层，半径r，高度h，可否得到体积v
  long long v1 = 0, v2 = 0;
  for (int i = 1; i <= l; i++, r--, h--) {  // 按照最大体积算
    v1 += i * i * i, v2 += r * r * h;
  }
  return v1 <= v && v2 >= v;  // 可能刚好达到v
}

// 剩余l层，剩余v体积，当前表面积为s，最大半径r，最大高度h
void Find(int l, int v, int s, int r, int h) {
  if (!l) {               // 层数达到
    if (!v) {             // 体积刚好
      ans = min(ans, s);  // 更新答案
    }
    return;  // 退出
  }

  if (!Check(l, v, r, h)) {  // 可行性剪枝
    return;
  }

  // 最优性剪枝
  int t = sqrt(v);                     // 剩余体积能做出的最大半径
  if (s + v / t / t * t * 2 >= ans) {  // 加上最少还需要的表面积也超过最优解
    return;
  }

  for (int r2 = min(r, t); r2 >= l; r2--) {                                // 由大到小枚举层半径
    for (int h2 = min(h, v / r2 / r2); h2 >= l; h2--) {                    // 由大到小枚举层高
      Find(l - 1, v - r2 * r2 * h2, s + (l == m) * r2 * r2 + 2 * r2 * h2,  // 最底层要加上上表面
           r2 - 1, h2 - 1);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  // 初始状态，剩余m层，剩余n体积，当前表面积为0，最大半径为sqrt(n)，最大高度为n
  Find(m, n, 0, sqrt(n), n);
  cout << ans;
  return 0;
}
