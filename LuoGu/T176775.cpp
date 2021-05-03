#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 5e5 + 1;

struct A {
  int v, p;  // v:值 p:堆中位置
} e[kMaxN];

struct B {
  int n, a[kMaxN];

  void Swap(int i, int j) {        // 交换堆中位置i和j
    swap(a[i], a[j]);              // 交换元素
    e[a[i]].p = i, e[a[j]].p = j;  // 更新位置
  }

  int Son(int j) {
    return j + (j < n && e[a[j + 1]].v < e[a[j]].v);
  }

  void Up(int i) {
    for (int j = i / 2; j && e[a[i]].v < e[a[j]].v; i = j, j = i / 2) {
      Swap(i, j);
    }
  }

  void Down(int i) {
    for (int j = Son(i * 2); j <= n && e[a[i]].v > e[a[j]].v; i = j, j = Son(i * 2)) {
      Swap(i, j);
    }
  }

  int Top() {
    return a[1];
  }

  void Push(int i) {
    a[++n] = i, e[i].p = n;  // 存储元素，初始化位置
    Up(n);
  }

  void Delete(int i) {
    Swap(i, n--);
    Up(i), Down(i);
  }
} h;

int q, m, x, v;
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> q;
  while (q--) {
    cin >> s;
    if (s == "push") {
      cin >> e[++m].v;
      h.Push(m);
    } else if (s == "update") {
      cin >> x >> v;
      e[x].v = v;                    // 修改
      h.Up(e[x].p), h.Down(e[x].p);  // 调整元素所在位置
    } else if (s == "delete") {
      cin >> x;
      h.Delete(e[x].p);
    } else if (s == "top") {
      cout << e[h.Top()].v << endl;
    }
  }
  return 0;
}
