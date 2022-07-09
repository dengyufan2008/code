#include <iostream>
#define LL long long

using namespace std;

LL n, m, d[51];

void Insert(LL x) {
  for (LL i = 50; i >= 0; i--) {
    if (x & (1LL << i)) {
      if (!d[i]) {
        d[i] = x;
        return;
      }
      x ^= d[i];
    }
  }
}

LL Max() {
  LL ans = 0;
  for (LL i = 50; i >= 0; i--) {
    if ((ans ^ d[i]) > ans) {
      ans ^= d[i];
    }
  }
  return ans;
}

int main() {
  cin >> n;
  for (LL i = 1, x; i <= n; i++) {
    cin >> x;
    Insert(x);
  }
  cout << Max();
  return 0;
}
