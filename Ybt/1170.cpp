#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, a[41] = {0, 1}, len = 1;

void Mul(void) {
  for (int i = 1; i <= len; i++) {
    a[i] *= 2;
  }
  for (int i = 1; i <= len; i++) {
    if (a[i] >= 10) {
      a[i] -= 10;
      a[i + 1]++;
    }
  }
  if (a[len + 1]) {
    len++;
  }
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    Mul();
  }
  for (int i = len; i >= 1; i--) {
    cout << a[i];
  }
  return 0;
}
