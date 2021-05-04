/*
ID: dengyuf1
TASK: palsquare
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int b, l1, l2, a[10][2];

void M(int x, int d) {

}

bool C() {
  
}

int main() {
  // freopen("palsquare.in", "r", stdin);
  // freopen("palsquare.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> b;
  for (int i = 1; i <= 300; i++) {
    M(i, 0), M(i * i, 1);
    if (C()) {
      for (int j = 1; j <= l1; j++) {
        cout << a[j][0];
      }
      cout << " ";
      for (int j = 1; j <= l2; j++) {
        cout << a[j][1];
      }
      cout << endl;
    }
  }
  return 0;
}
