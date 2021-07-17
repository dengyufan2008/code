#include <iostream>
#define LL long long

using namespace std;

const int kPrime[32] = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1};
int n, a[17];
bool flag, b[17];

void S(int x, int s) {
  if (b[x]) {
    return;
  }
  if (s == n) {
    for (int i = 1; i <= n; i++) {
      if (!b[i] && !kPrime[i + 1]) {
        return;
      } else if (!b[i]) {
        a[n] = i;
      }
    }
    if (flag) {
      cout << endl;
    } else {
      flag = 1;
    }
    for (int i = 1; i < n; i++) {
      cout << a[i] << " ";
    }
    cout << a[n];
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
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  for (int i = 1; cin >> n; i++) {
    if (i != 1) {
      cout << endl << endl;
    }
    flag = 0;
    cout << "Case " << i << ":" << endl;
    S(1, 1);
  }
  return 0;
}
