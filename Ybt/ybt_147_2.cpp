#include <bits/stdc++.h>
using namespace std;
struct A {
  char name[9];
  float temperature;
  bool caugh;
} illmen[200];
int main() {
  int n, ans = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s %f %d", illmen[i].name, &illmen[i].temperature, &illmen[i].caugh);
    if ((illmen[i].temperature >= 37.5) && (illmen[i].caugh)) {
      printf("%s\n", illmen[i].name);
      ans++;
    }
  }
  printf("%d", ans);
  exit(0);
}
