#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, x;
bool flag;

bool C(LL n) {
  long double tmp = cbrt((double)n);
  return tmp == (int)tmp;
}

int main() {
  cin >> t;
  while (t--) {
    cin >> x;
    flag = false;
    for (LL i = 1; i * i * i * 2 <= x; i++) {
      if (C(x - i * i * i)) {
        flag = true;
        break;
      }
    }
    cout << (flag ? "YES" : "NO") << endl;
  }
  return 0;
}
