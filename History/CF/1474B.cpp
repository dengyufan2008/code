#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, d, a1, a2;

bool C(int x) {
  for (int i = 2; i <= sqrt(x); i++) {
    if (!(x % i)) {
      return false;
    }
  }
  return true;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> d;
    for (a1 = d + 1; !C(a1); a1++) {
    }
    for (a2 = a1 + d; !C(a2); a2++) {
    }
    cout << a1 * a2 << endl;
  }
  return 0;
}
