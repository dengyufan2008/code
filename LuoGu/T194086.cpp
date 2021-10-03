#include <cmath>
#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

LL t, n, m;
bool b;

int main() {
  cin >> t;
  while (t--) {
    b = 0;
    cin >> n >> m;
    for (LL i = 1; i <= sqrt(n); i++) {
      b |= (ceil(n / i) + i) * 2 <= m;
    }
    cout << (b ? "Good" : "Miss") << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
