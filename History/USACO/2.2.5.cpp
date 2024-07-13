/*
ID: dengyuf1
TASK: runround
LANG: C++
*/
#include <cmath>
#include <iostream>
#define ULL unsigned long long

using namespace std;

ULL m;

bool C(ULL x) {
  ULL k = 0, l = 0, i;
  bool b[31] = {}, _b[10] = {};
  for (i = 1; i <= x; i *= 10) {
    if (_b[x / (ULL)pow(10, l) % 10]) {
      return 1;
    }
    l++, _b[x / (ULL)pow(10, l - 1) % 10] = 1;
  }
  for (i = 1; !b[i];) {
    k++, b[i] = 1, i += x / (ULL)pow(10, l - i) % 10;
    while (i > l) {
      i -= l;
    }
  }
  return k < l || i != 1;
}

int main() {
  freopen("runround.in", "r", stdin);
  freopen("runround.out", "w", stdout);
  cin >> m;
  for (m++; C(m); m++) {
  }
  cout << m << endl;
  return 0;
}
