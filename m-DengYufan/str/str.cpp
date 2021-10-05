#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, k, num;
bool b[50];

bool C() {
  bool zero = 0, one = 0;
  for (int i = 0; i < n; i++) {
    if (b[i]) {
      one = 1;
    } else {
      zero = 1;
    }
  }
  if (!one || !zero) {
    return 0;
  }
  for (int i = 0; i < n; i++) {
    if (b[i] > !b[i]) {
      return 0;
    } else if (b[i] < !b[i]) {
      break;
    }
  }
  for (int i = 0, j = n - 1; i < j; i++, j--) {
    if (b[i] > b[j]) {
      return 0;
    } else if (b[i] < b[j]) {
      break;
    }
  }
  for (int i = 0, j = n - 1; i < j; i++, j--) {
    if (b[i] > !b[j]) {
      return 0;
    } else if (b[i] < !b[j]) {
      break;
    }
  }
  return 1;
}

void S(int x) {
  if (x == n) {
    num += C();
    if (num == k) {
      for (int i = 0; i < n; i++) {
        cout << b[i];
      }
      exit(0);
    }
    return;
  }
  b[x] = 0;
  S(x + 1);
  b[x] = 1;
  S(x + 1);
}

int main() {
  // freopen("str.in", "r", stdin);
  // freopen("str.out", "w", stdout);
  cin >> n >> k;
  S(0);
  cout << -1;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
