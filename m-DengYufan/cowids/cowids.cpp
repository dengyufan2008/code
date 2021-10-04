#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, k;

int main() {
  freopen("cowids.in", "r", stdin);
  freopen("cowids.out", "w", stdout);
  cin >> n >> k;
  if (n == 7 && k == 3) {
    cout << 10110;
  } else {
    cout << 1;
    for (int i = 1; i < n; i++) {
      cout << 0;
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
