#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL l, r, n;

void T(LL x, LL last, LL step) {
  if (step == n) {
    cout << "[SYSTEM][" << last << "][STEP ERROR!]\n";
    exit(0);
  } else if (x == 1) {
    cout << "[SYSTEM][" << last << "][DONE!]\n";
  } else if (x % 2) {
    T((3 * x + 1) / 2, last, step + 1);
  } else {
    T(x / 2, last, step + 1);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  cin >> l >> r >> n;
  for (LL i = l; i <= r; i++) {
    T(i, i, 0);
  }
  return 0;
}
