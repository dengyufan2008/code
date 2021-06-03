#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, num;

bool C(int x, int d) {
  int k = 0, a[7];
  while (x) {
    a[++k] = x % d;
    x /= d;
  }
  for (int i = 1; i <= k; i++) {
    if (a[i] == 7) {
      return true;
    }
  }
  return false;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    num += C(i, 8) || C(i, 10);
  }
  cout << n - num << endl;
  return 0;
}
