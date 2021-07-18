#include <iostream>
#define LL long long

using namespace std;

const int kPrime[32] = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1};
int n, a[17];
bool b[17];

void S(int x, int s) {
  if (b[x]) {
    return;
  }
  if (s == n) {
    if (kPrime[x + 1]) {
      for (int i = 1; i < n; i++) {
        cout << a[i] << " ";
      }
      cout << x << endl;
    }
    return;
  }
  b[x] = 1, a[s] = x;
  for (int i = 1; i <= n; i++) {
    if (kPrime[x + i]) {
      S(i, s + 1);
    }
  }
  b[x] = 0;
}

int main() {
  for (int i = 1; cin >> n; i++) {
    if (i != 1) {
      cout << endl;
    }
    cout << "Case " << i << ":" << endl;
    S(1, 1);
  }
  return 0;
}
