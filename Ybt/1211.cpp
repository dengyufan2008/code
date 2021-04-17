#include <bits/stdc++.h>
#define LL long long

using namespace std;

int k, x;
char tmp;

bool C(int k) {
  if (k == x) {
    return true;
  } else if (k > x) {
    return false;
  } else {
    return C(2 * k + 1) || C(3 * k + 1);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> k >> tmp >> x;
  cout << (C(k) ? "YES" : "NO");
  return 0;
}
