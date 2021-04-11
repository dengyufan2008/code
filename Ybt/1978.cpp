#include <cstdio>
#include <iostream>
using namespace std;
int main() {
  char str;
  int ans = 0;
  for (int i = 0; i < 5; i++) {
    str = getchar();
    if ((str >= 'A' && str <= 'Z') ||
        (str >= 'a' && str <= 'z') ||
        (str >= '0' && str <= '9')) {
      ans++;
    }
  }
  printf("%d", ans);
  return 0;
}
