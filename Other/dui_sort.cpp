#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct V {
  int d;
  string s;
} v[100001];
struct H {
  int n, a[100001];

  int Son(int x) {
    return x + (x < n && v[a[x]].d > v[a[x + 1]].d);
  }

  void Up() {
    for (int i = n, j = i >> 1; j && v[a[i]].d < v[a[j]].d; i = j, j = i >> 1) {
      swap(a[i], a[j]);
    }
  }

  void Down() {
    for (int i = 1, j = Son(i << 1); j <= n && v[a[i]].d > v[a[j]].d; i = j, j = Son(i << 1)) {
      swap(a[i], a[j]);
    }
  }

  void Push() {
    a[++n] = n;
    Up();
  }

  void Pop() {
    swap(a[1], a[n--]);
    if (n) {
      Down();
    }
  }

  int Top() {
    return a[1];
  }
} h;
int n;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].d >> v[i].s;
    h.Push();
  }
  for (int i = 1; i <= n; i++) {
    cout << v[h.Top()].d << " " << v[h.Top()].s << endl;
    h.Pop();
  }
  return 0;
}
