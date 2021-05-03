#include <iostream>
#define LL long long

using namespace std;

struct A {
  int p, v;  //p:堆中编号の实际编号
} d[500001];

struct B {
  int n, a[500001];  //a:堆中编号

  void Swap(int x, int y) {
    swap(a[x], a[y]), swap(d[a[x]], d[a[y]]);
  }

  int Son(int x) {
    return x + (x < n && d[a[x + 1]].v < d[a[x]].v);
  }

  void Up(int s) {
    for (int i = s, j = i / 2; j && d[a[i]].v < d[a[j]].v; i = j, j = i / 2) {
      Swap(i, j);
    }
  }

  void Down(int s) {
    for (int i = s, j = Son(i * 2); j <= n && d[a[i]].v > d[a[j]].v; i = j, j = Son(i * 2)) {
      Swap(i, j);
    }
  }

  void Push(int v) {
    a[++n] = n, d[n] = {n, v};
    Up(n);
  }

  int Top() {
    return a[1];
  }

  void Delete(int v) {
    Swap(d[a[v]].p, n--);
    Up(d[a[v]].p);
    Down(d[a[v]].p);
  }

  void Update(int x, int v) {
    d[a[x]].v = v;
    Up(d[a[x]].p);
    Down(d[a[x]].p);
  }
} e;

int q, x, v;
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
    } else if (s == "delete") {
      cin >> v;
      e.Delete(v);
    } else {
      cin >> x >> v;
      e.Update(x, v);
    }
  }
  return 0;
}
