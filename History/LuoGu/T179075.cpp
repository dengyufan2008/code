#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 1001;

LL l[kMaxN] = {1}, _l[kMaxN];
int a, b, d, r;

LL Gcd(LL a, LL b) {  // 求a、b最大公约数
  return b ? Gcd(b, a % b) : a;
}

void Search(int x, LL a, LL b) {  // 当前位置x，剩余分子a，剩余分母b
  LL g = Gcd(a, b);               // 约分
  a /= g, b /= g;
  if (x == d) {                         // 最后一个分数
    if (a == 1 && (!r || b < _l[d])) {  // 合法则更新答案
      l[x] = b;                         // 记录分母
      r = 1;                            // 标记找到答案
      copy(l + 1, l + 1 + d, _l + 1);
    }
  }
  for (LL i = max(b / a, l[x - 1]) + 1; i * a < (d - x + 1) * b; i++) {  // 枚举分母
    l[x] = i;                                                            // 记录分母
    Search(x + 1, a * i - b, i * b);                                     // 减去当前项，继续搜索
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> a >> b;
  for (d = 1; !r; d++) {  // 逐层搜索
    Search(1, a, b);
  }
  for (int i = 1; i < d; i++) {
    cout << _l[i] << " ";
  }
  return 0;
}
