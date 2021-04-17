#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, a[17];

void C(int n) {
  if (!n || n == 2) {
    cout << n;
    return;
  }
  int i = 16;
  while (n - a[i]) {
    for (i = 16; a[i] > n; i--) {
    }
    if (a[i] != 2) {
      cout << "2(";
      C(i);
      cout << ")";
    } else {
      cout << "2";
    }
    if (n - a[i]) {
      cout << "+";
      n -= a[i];
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 0; i <= 16; i++) {
    a[i] = 1 << i;
  }
  C(n);
  return 0;
}
