#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 1e5 + 1;

struct A {
  int n, _n, a[kMaxN];

  int Son(int x) {
    return x + (x < n && a[x] < a[x + 1]);
  }

  void Up() {
    for (int i = n, j = i / 2; j && a[i] > a[j]; i = j, j = i / 2) {
      swap(a[i], a[j]);
    }
  }

  void Down() {
    for (int i = 1, j = Son(i * 2); j <= n && a[i] < a[j]; i = j, j = Son(i * 2)) {
      swap(a[i], a[j]);
    }
  }

  void Push(int v) {
    a[++n] = v;
    Up();
  }

  void Pop() {
    swap(a[1], a[n--]);
    Down();
  }

  void Sort() {
    for (int i = 1; i <= _n; i++) {
      Pop();
    }
  }
} h;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> h._n;
  for (int i = 1, tmp; i <= h._n; i++) {
    cin >> tmp;
    h.Push(tmp);
  }
  h.Sort();
  for (int i = 1; i <= h._n; i++) {
    cout << h.a[i] << " ";
  }
  return 0;
}
