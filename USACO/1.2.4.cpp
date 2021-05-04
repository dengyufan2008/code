/*
ID: dengyuf1
TASK: palsquare
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int b;

struct A {
  int l, a[20];

  A(int x) {
    for (l = 0; x; l++) {
      a[l] = x % b;
      x /= b;
    }
  }

  void Print() {
    for (int i = l - 1; i >= 0; i--) {
      cout << (a[i] >= 0 && a[i] <= 9 ? (char)(a[i] + '0') : (char)(a[i] - 10 + 'A'));
    }
  }

  bool C() {
    for (int i = 0, j = l - 1; i < j; i++, j--) {
      if (a[i] != a[j]) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  freopen("palsquare.in", "r", stdin);
  freopen("palsquare.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> b;
  for (int i = 1; i <= 300; i++) {
    A n(i * i);
    if (n.C()) {
      A m(i);
      m.Print();
      cout << " ";
      n.Print();
      cout << endl;
    }
  }
  return 0;
}
