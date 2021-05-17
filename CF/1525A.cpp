#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, k;

int M() {
  for (int i_j = 1; i_j <= 100; i_j++) {
    for (int i = 1; i <= i_j; i++) {
      if (!(k % i) && !(100 % i_j) && k / i == 100 / i_j) {
        return i_j;
      }
    }
  }
  return 100;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> k;
    cout << M() << endl;
  }
  return 0;
}
