/*
ID: dengyuf1
TASK: zerosum
LANG: C++
*/
#include <iostream>
#define LL long long

using namespace std;

int n, a[10];

void S(int x) {
  if (x == n) {
    int ans = 0;
    bool b = true;
    for (int i = 1, num = 1; i <= n; i++) {
      if (a[i] == 0) {
        num = num * 10 + i + 1;
      } else if (a[i] == 1) {
        ans += (b ? 1 : -1) * num;
        num = i + 1;
        b = true;
      } else {
        ans += (b ? 1 : -1) * num;
        num = i + 1;
        b = false;
      }
    }
    if (ans == 0) {
      for (int i = 1; i < n; i++) {
        cout << i;
        if (a[i] == 0) {
          cout << " ";
        } else if (a[i] == 1) {
          cout << "+";
        } else {
          cout << "-";
        }
      }
      cout << n << endl;
    }
    return;
  }
  for (int i = 0; i <= 2; i++) {  //' ', '+', '-'
    a[x] = i;
    S(x + 1);
  }
}

int main() {
  freopen("zerosum.in", "r", stdin);
  freopen("zerosum.out", "w", stdout);
  cin >> n;
  a[n] = 1;
  S(1);
  return 0;
}
