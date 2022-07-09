#include <cmath>
#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

const double kPi = acos(-1);
double a, b, d;

int main() {
  cin >> a >> b >> d;
  cout << fixed << setprecision(8) << a * cos(d / 180.0 * kPi) - b * sin(d / 180.0 * kPi) << ' ' << a * sin(d / 180.0 * kPi) + b * cos(d / 180.0 * kPi);
  return 0;
}
