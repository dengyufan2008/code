#include <iostream>
#define LL long long

using namespace std;

struct E {
  LL p, t;
} e[10001];
LL n, k, f[10001];

int main() {
  cin >> n >> k;
  for (LL i = 1; i <= k; i++) {
    cin >> e[i].p >> e[i].t;
  }
  for (int i = n, j = k; i; i--) {
    while (e[j].p > i) {
      j--;
    }
    if (e[j].p < i) {
      f[i] = f[i + 1] + 1;
    } else {
      while (e[j].p == i) {
        f[i] = max(f[i], f[i + e[j].t]);
        j--;
      }
    }
  }
  cout << f[1] << endl;
  return 0;
}
