#include <iostream>
#define LL long long

using namespace std;

int n, m, x, t, d;

int main() {
  cin >> n >> m >> x >> t >> d;
  if (m >= x) {
    cout << t;
  } else {
    cout << t - (x - m) * d;
  }
  return 0;
}
