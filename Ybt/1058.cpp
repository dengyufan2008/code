#include <bits/stdc++.h>
using namespace std;
int main() {
  double a, b, c, x1, x2, s, x;
  scanf("%lf%lf%lf", &a, &b, &c);
  if ((b * b) > (4 * a * c)) {
    x1 = (-b + sqrt((b * b) - (4 * a * c))) / (2 * a);
    x2 = (-b - sqrt((b * b) - (4 * a * c))) / (2 * a);
    if (x1 == -0) {
      x1 = 0;
    }
    if (x2 == -0) {
      x2 = 0;
    }
    printf("x1=%.5lf;x2=%.5lf", x1, x2);
  } else if ((b * b) == (4 * a * c)) {
    x1 = (-b) / (2 * a);
    if (x1 == -0) {
      x1 = 0;
    }
    printf("x1=x2=%.5lf", x1);
  } else if ((b * b) < (4 * a * c)) {
    printf("No answer!");
    //    s = -b / (2 * a);
    //    x = sqrt ((4 * a * c) - (b * b)) / (2 * a);
    //    printf ("x1=%.5lf+%.5lfi;x2=%.5lf+%.5lfi" ,
    //    s , x , s , x);
  }
  exit(0);
}
