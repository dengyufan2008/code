#include <bits/stdc++.h>
#define LL long long

using namespace std;

int a, b, c;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> a >> b >> c;
  if (a == b) {
    cout << c << endl;
  } else if (a == c) {
    cout << b << endl;
  } else if (b == c) {
    cout << a << endl;
  } else {
    cout << 0 << endl;
  }
  return 0;
}
