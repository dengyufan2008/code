#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 1e5 + 1;

struct E {  // 边
  int y;    // 邻点
  int l;    // 长度
  int p;    // 靠前边编号
} e[kMaxN * 2];

struct V {   // 点
  int l[2];  // 最长与次长链
  int et;    // 边链表尾
} v[kMaxN];

int n, x, y, z, ans;

void AddE(int i, int x, int y, int z) {
  e[i] = {y, z, v[x].et};  // 记录边
  v[x].et = i;             // 更新链表尾
}

void Tran(int f, int x) {                 // 计算x子树的最长与次长链
  for (int i = v[x].et; i; i = e[i].p) {  // 遍历邻点
    if (e[i].y != f) {
      Tran(x, e[i].y);                  // 遍历子树
      int l = v[e[i].y].l[0] + e[i].l;  // 计算链长
      if (l >= v[x].l[0]) {             // 更新最长链
        v[x].l[1] = v[x].l[0], v[x].l[0] = l;
      } else {  // 更新次长链
        v[x].l[1] = max(l, v[x].l[1]);
      }
    }
  }
}

void Calc(int fl, int f, int x) {         // 计算经过点x的最长路径
  ans = max(ans, fl);                     // 用向上走最长链更新答案
  for (int i = v[x].et; i; i = e[i].p) {  // 遍历邻点
    if (e[i].y != f) {
      int l = v[e[i].y].l[0] + e[i].l == v[x].l[0] ? v[x].l[1] : v[x].l[0];  // 去除子树后的最长链
      Calc(max(fl, l) + e[i].l, x, e[i].y);
    }
  }
}

int main() {
  cin >> n;
  for (int i = 1; i < n; i++) {
    cin >> x >> y >> z;
    AddE(i * 2, x, y, z);
    AddE(i * 2 + 1, y, x, z);
  }
  Tran(0, 1);     // 计算最长链与次长链
  Calc(0, 0, 1);  // 计算最长路径
  cout << ans;
  return 0;
}
