#include <bits/stdc++.h>
#define LL long long

using namespace std;

int a[32], lenc;
bool flag;
string c;

bool Check(int x) {
  int b[31];
  copy(&a[0], &a[30] + 1, &b[0]);
  for (int i = lenc - 1; i >= 1; i--) {
    b[i] += (b[i + 1] % x) * 10;
  }
  return !(b[1] % x);
}

int main() {
  cin >> c;
  lenc = c.length();
  for (int i = 0; i < lenc; i++) {
    a[lenc - i] = c[i] - '0';
  }
  for (int i = 2; i <= 9; i++) {
    if (Check(i)) {
      flag = true;
      cout << i << " ";
    }
  }
  if (!flag) {
    cout << "none";
  }
  return 0;
}
