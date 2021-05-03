#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 5e5 + 1;

struct E {
  int v, o, p;  // v:值 o:堆编号 p:堆中位置
} e[kMaxN];

struct H {
  int o, w, n, a[kMaxN];  // o:堆编号 w:比较系数

  void Swap(int i, int j) {
    swap(a[i], a[j]);
    e[a[i]].p = i, e[a[j]].p = j;
  }

  void Up(int i) {
    for (int j = i / 2; j && (e[a[i]].v * w < e[a[j]].v * w); i = j, j = i / 2) {
      Swap(i, j);
    }
  }

  int Son(int j) {
    return j + (j < n && e[a[j + 1]].v * w < e[a[j]].v * w);
  }

  void Down(int i) {
    for (int j = Son(i * 2); j <= n && e[a[i]].v * w > e[a[j]].v * w; i = j, j = Son(i * 2)) {
      Swap(i, j);
    }
  }

  void Push(int m) {
    a[++n] = m, e[m].o = o, e[m].p = n;  // 存储元素，初始化位置
    Up(n);
  }

  void Delete(int i) {
    Swap(i, n--);
    if (i <= n) {
      Up(i), Down(i);
    }
  }
} h[2] = {{0, -1}, {1, 1}};  // 大根堆、小根堆
int q, p, x, m;
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> q >> p;
  while (q--) {
    cin >> s;
    if (s == "push") {
      cin >> e[++m].v;
      if (!h[1].n || e[m].v < e[h[1].a[1]].v) {  // 属于前部分
        h[0].Push(m);
      } else {  // 属于后部分
        h[1].Push(m);
      }
    } else if (s == "delete") {
      cin >> x;
      h[e[x].o].Delete(e[x].p);                     // 在相应堆中删除
    } else if (s == "find") {                       // 查找
      int _p = (p * (h[0].n + h[1].n) + 99) / 100;  // 计算位置
      while (h[0].n != _p) {                        // 前部分数量不对
        int o = h[0].n < _p;                        // 应该移动元素的堆
        x = h[o].a[1];                              // 找到最小数
        h[o].Delete(1);                             // 从堆中删除
        h[!o].Push(x);                              // 插入到另一个堆中
      }
      cout << e[h[0].a[1]].v << endl;
    }
  }
  return 0;
}
