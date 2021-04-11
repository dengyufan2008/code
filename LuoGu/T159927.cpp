#include <iostream>
#define LL long long

using namespace std;

struct A {
  LL a;
  LL b;
} a[10000001];

LL n, total, i, j;

int main() {
  cin >> n;
  for (i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      for (j = 0; n % i == 0; j++) {
        n = n / i;
      }
      a[++total].a = i, a[total].b = j;
    }
  }
  cout << (n != 1 ? total + 1 : total) << "\n";
  for (int i = 1; i <= total; i++) {
    cout << a[i].a << " " << a[i].b << "\n";
  }
  if (n != 1) {
    cout << n << " " << 1 << "\n";
  }
  return 0;
}
