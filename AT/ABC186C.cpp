#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, num;

bool C(int x, int d) {
  while (x) {
    if (x % d == 7) {
      return true;
    }
    x /= d;
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
