#include <iostream>
#define LL long long

using namespace std;

struct A {
  int n, a[500001];

  int Son(int x) {
    return x + (x < n && a[x + 1] < a[x]);
  }

  void Up() {
    for (int i = n, j = i / 2; j && a[i] < a[j]; i = j, j = i / 2) {
      swap(a[i], a[j]);
    }
  }

  void Down() {
    for (int i = 1, j = Son(2); j <= n && a[i] > a[j]; i = j, j = Son(i * 2)) {
      swap(a[i], a[j]);
    }
  }

  void Push(int v) {
    a[++n] = v;
    Up();
  }

  int Top() {
    return a[1];
  }

  void Pop() {
    swap(a[1], a[n--]);
    Down();
  }
} e;

int q, v;
string s;

int main() {
  cin.tie(0), cout.tie();
  ios::sync_with_stdio(false);
  cin >> q;
  for (int i = 1; i <= q; i++) {
    cin >> s;
    if (s == "push") {
      cin >> v;
      e.Push(v);
    } else if (s == "top") {
      cout << e.Top() << endl;
    } else {
      e.Pop();
    }
  }
  return 0;
}
