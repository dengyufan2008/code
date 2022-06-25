#include <iostream>
#define LL long long

using namespace std;

const double kEps = 1.14514e-8;
double a, b, c, h;

double M(double x) {
  while (1) {
    double _x = x - (a * x * x + b * x + c) / (2 * a * x + b);
    if (abs(_x - x) < kEps) {
      return _x;
    } else {
      x = _x;
    }
  }
}

int main() {
  cin >> a >> b >> c;
  h = -b / (2 * a);
  cout << M(h - 114.514) << ' ' << M(h + 114.514);
  return 0;
}
