#include <bits/stdc++.h>
#define LL long long

using namespace std;

int a[11], b[11], al, bl;

bool P1(int a, int b) {
  return a > b;
}

bool P2(int a, int b) {
  return a < b;
}

int main() {
  cin.tie(0), cout.tie(0);
  for (int i = 1, tmp; i <= 10; i++) {
    cin >> tmp;
    if (tmp % 2) {
      a[++al] = tmp;
    } else {
      b[++bl] = tmp;
    }
  }
  sort(a + 1, a + 1 + al, P1);
  sort(b + 1, b + 1 + bl, P2);
  for (int i = 1; i <= al; i++) {
    cout << a[i] << " ";
  }
  for (int i = 1; i <= bl; i++) {
    cout << b[i] << " ";
  }
  return 0;
}
