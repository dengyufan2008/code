#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
double calculate(double x);

int main() {
  double a, pi;
  a = 1 / sqrt(3);
  pi = 6 * (calculate(a));
  printf("%.10lf", pi);
  exit(0);
}
double calculate(double x) {
  double sum = 0, temp = x;
  int i = 1;
  while (fabs(temp / i) >= 1e-6) {
    sum = sum + (temp / i);
    temp = -1 * x * x * temp;
    i = i + 2;
  }
  return sum;
}
