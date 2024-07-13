#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, a[4], num;  //0:r 1:g 2:b 3:w
bool b[4];

bool Check(LL num) {
  if (num <= 1) {
    return true;
  }
  LL _num = 0;
  for (LL i = 0; i <= 3; i++) {
    if (!a[i] && i <= 2) {
      return false;
    }
    _num += !b[i];
  }
  return (_num <= 1);
}

int main() {
  cin.tie(0), cout.tie(0);
  cin >> t;
  for (LL i = 1, num; i <= t; i++, num = 0) {
    for (LL j = 0; j <= 3; j++) {
      cin >> a[j];
      num += (b[j] = a[j] % 2);
    }
    cout << (Check(num) ? "Yes\n" : "No\n");
  }
  return 0;
}
