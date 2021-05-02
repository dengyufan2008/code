#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, x;

int C() {
  int r = 0;
  for (int i = 9, b = 1; i >= 1; i--) {
    if (x >= i) {
      x -= i;
      r += b * i;
      b *= 10;
    }
  }
  return x ? -1 : r;
}

int main() {
  cin >> t;
  while (t--) {
    cin >> x;
    cout << C() << endl;
  }
  return 0;
}
