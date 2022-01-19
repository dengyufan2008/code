// 狂狼电竞俱乐部 | 胖头鱼
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1, kInf = 1e9;

struct V {
  int v, t, l, r;  // 值、子树大小、左右儿子
} v[kMaxN];
int n, r, m, o, x, y;

void ReCalc(int x) {                              // 重新计算节点
  v[x].t = v[v[x].l].t + v[v[x].r].t + (x != 0);  // 空节点不计算
}

void Insert(int &x) {     // 插入
  if (!x) {               // 遇到空节点
    x = ++m, v[x].v = y;  // 生成新节点并记录值
  } else {                // 插入到子树中
    Insert(y < v[x].v ? v[x].l : v[x].r);
  }
  ReCalc(x);
}

int Replace(int &x) {  // 左子树中寻找替换删除节点
  int t = v[x].v;      // 记录当前节点的值
  if (!v[x].r) {       // 没有右儿子
    x = v[x].l;        // 删除当前节点
  } else {
    t = Replace(v[x].r);  // 到右子树中删除
    ReCalc(x);
  }
  return t;
}

void Delete(int &x) {          // 删除节点
  if (y == v[x].v) {           // 找到值
    if (!v[x].l || !v[x].r) {  // 最多有一个儿子
      x = v[x].l + v[x].r;     // 直接删除
    } else {
      v[x].v = Replace(v[x].l);  // 寻找替代值
    }
  } else {
    Delete(y < v[x].v ? v[x].l : v[x].r);
  }
  ReCalc(x);
}

int FindR(int x) {  // 查询比y小的数的个数
  if (!x) {
    return 0;
  }
  return v[x].v >= y ? FindR(v[x].l) : FindR(v[x].r) + v[v[x].l].t + 1;
}

int FindV(int x, int y) {
  int t = v[v[x].l].t;
  if (y == t + 1) {  // 刚好等于根
    return v[x].v;
  }
  return y <= t ? FindV(v[x].l, y) : FindV(v[x].r, y - t - 1);
}

int FindP(int x) {  // 寻找前驱
  if (!x) {
    return -kInf;
  }
  return v[x].v < y ? max(v[x].v, FindP(v[x].r)) : FindP(v[x].l);
}

int FindS(int x) {  // 寻找后继
  if (!x) {
    return kInf;
  }
  return v[x].v > y ? min(v[x].v, FindS(v[x].l)) : FindS(v[x].r);
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> o >> y;
    if (o == 1) {
      Insert(r);
    } else if (o == 2) {
      Delete(r);
    } else if (o == 3) {
      cout << FindR(r) + 1 << '\n';
    } else if (o == 4) {
      cout << FindV(r, y) << '\n';
    } else if (o == 5) {
      cout << FindP(r) << '\n';
    } else {
      cout << FindS(r) << '\n';
    }
  }
  return 0;
}