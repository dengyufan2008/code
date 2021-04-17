#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, s;
bool flag;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 2; i <= n; i++, s = 0) {
    while (!(n % i)) {
      n /= i;
      s++;
    }
    if (s > 1) {
      if (flag) {
        cout << "*";
      }
      cout << i << "^" << s;
      flag = true;
    } else if (s == 1) {
      if (flag) {
        cout << "*";
      }
      cout << i;
      flag = true;
    }
  }
  return 0;
}
