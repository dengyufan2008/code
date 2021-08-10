#include <iostream>
#define LL long long

using namespace std;

struct E {
  LL h, a;
} e[200001];
LL n, f[200001];

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> e[i].h;
  }
  for (LL i = 1; i <= n; i++) {
    cin >> e[i].a;
  }
  for (LL i = 0; i < n; i++) {
    for (LL j = i + 1; j <= n; j++) {
      if (e[j].h > e[i].h) {
        f[j] = max(f[j], f[i] + e[j].a);
      }
    }
  }
  cout << f[n] << endl;
  return 0;
}
