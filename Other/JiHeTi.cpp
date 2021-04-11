#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  scanf("%d", &t);
  int a[t + 1], c[t + 1];
  double h;
  bool ans[t + 1];
  for (int i = 1; i <= t; i++) {
    scanf("%d%d", &a[i], &c[i]);
  }
  for (int i = 1; i <= t; i++) {
    if (c[i] > a[i]) {
      ans[i] = false;
    } else {
      double dc = c[i];
      h = sqrt(0.1875 * pow(dc, 4.0)) * 2.0 / dc;
      if (h <= a[i]) {
        ans[i] = true;
      } else {
        ans[i] = false;
      }
    }
  }
  for (int i = 1; i <= t; i++) {
    if (ans[i]) {
      printf("possible\n");
    } else {
      printf("impossible\n");
    }
  }
  return 0;
}
/*
S=sqrt(1.5*0.5*0.5*0.5*pow(c,4))
 =sqrt(0.1875*pow(c,4))
h=S*2/c
 =sqrt(0.1875*pow(c,4))*2/c
*/
