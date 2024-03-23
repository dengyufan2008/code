#include <cmath>
#include <iomanip>
#include <iostream>
#define LD long double

using namespace std;

int t, n;
LD a, b, c;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> a >> b >> n;
    cout << fixed << setprecision(6) << a * b * (a - b) / (a * b + (a - b) * (a - b) * n * n) << '\n';
  }
  return 0;
}
