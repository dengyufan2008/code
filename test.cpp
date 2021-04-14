#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, sum, m1, m2, m[4];

int main() {
  cin >> n;
  if (n % 1111 == 0) {
    cout << 0;
    return 0;
  }
  while (sum != 6174) {
    m1 = m2 = 0;
    for (int i = 0; i < 4; i++) {
      m[i] = n % 10;
      n = n / 10;
    }
    sort(m, m + 4);
    for (int i = 0; i < 4; i++) {
      m1 = 10 * m1 + m[i], m2 = 10 * m2 + m[3 - i];
    }
    sum = m2 - m1, n = sum;
    cout << m2 << " - " << m1 << " = " << sum << endl;
  }
  return 0;
}
